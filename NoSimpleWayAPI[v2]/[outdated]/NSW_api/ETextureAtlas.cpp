#include "ETextureAtlas.h"
#include <NSW_api\EUtils.h>

bool ETextureAtlas::can_place_here(int _x, int _y, int _w, int _h)
{
	for (int j = _x; j <= _x + _w; j++)
		for (int i = _y; i <= _y + _h; i++)
		{
			if ((j >= 1024) || (i >= 1024))
			{
				return false;
			}

			if (!free_space[j][i]) { return false; }
		}

	return true;
}

EGabarite* ETextureAtlas::put_texture_to_atlas(std::string _name, ETextureAtlas* _ta)
{
	for (int i = 0; i < _name.length(); i++)
	{
		if (_name[i] == '\\') { _name[i] = '/'; }
	}

	EGabarite* duplicate_gabarite = NULL;

	//search already loaded texture gabarite
	for (EGabarite* g : EGraphicCore::gabarite_list)
	{
		if (g->name == _name)
		{
			duplicate_gabarite = g;
		}
	}

	EGabarite* new_gabarite = NULL;
	if (duplicate_gabarite == NULL)
	{
		glViewport(0, 0, _ta->size_x, _ta->size_y);
		glBindFramebuffer(GL_FRAMEBUFFER, _ta->framebuffer);

		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//set correct zoom
		EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1, -1, 0.0f));
		EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(1.0f / _ta->size_x * 2.0f, 1.0f / _ta->size_y * 2.0f, 1));

		//use shader
		EGraphicCore::ourShader->use();

		unsigned int transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, EGraphicCore::texture[0]);
		EGraphicCore::ourShader->setInt("texture1", 0);
		EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);

		EGraphicCore::load_texture(_name.c_str(), 0);
		//std::cout << "no dublicates with <" << _name << ">" << std::endl;

		int place_x = 0;
		int place_y = 0;
		for (int x = 0; x < 1024; x++)
			for (int y = 0; y < 1024; y++)
			{
				if (_ta->can_place_here(x, y, ceil(EGraphicCore::last_texture_w / 4.0f), ceil(EGraphicCore::last_texture_h / 4.0f)))
				{
					place_x = x * 4;
					place_y = y * 4;

					x = 99999;
					y = 99999;
				}
			}

		for (int x = (ceil)(place_x / 4.0f) - 2; x < (ceil)((place_x + EGraphicCore::last_texture_w) / 4.0f) + 2; x++)
			for (int y = (ceil)(place_y / 4.0f) - 2; y < (ceil)((place_y + EGraphicCore::last_texture_h) / 4.0f) + 2; y++)
				if ((x < 1024) & (y < 1024) & (x >= 0) & (y >= 0))
				{
					_ta->free_space[x][y] = false;
				}

		EGraphicCore::batch->reset();

		/*glBlendEquation(GL_MAX);
		EGraphicCore::batch->draw_rect(place_x - 1, place_y + 1, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x + 0, place_y + 1, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x + 1, place_y + 1, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x - 1, place_y + 0, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x + 1, place_y + 0, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x - 1, place_y - 1, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x + 0, place_y - 1, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x + 1, place_y - 1, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);

		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();*/

		/*EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.0f);
		glBlendEquation(GL_MIN);
		EGraphicCore::batch->draw_rect(place_x, place_y, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);

		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();*/

		EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
		glBlendEquation(GL_MAX);

		EGraphicCore::batch->draw_rect(place_x - 1.0f, place_y - 1.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x - 0.0f, place_y - 1.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x + 1.0f, place_y - 1.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);

		EGraphicCore::batch->draw_rect(place_x - 1.0f, place_y - 0.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x - 0.0f, place_y - 0.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x + 1.0f, place_y - 0.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);

		EGraphicCore::batch->draw_rect(place_x - 1.0f, place_y + 1.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x - 0.0f, place_y + 1.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->draw_rect(place_x + 1.0f, place_y + 1.0f, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);

		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();

		glBlendEquation(GL_MIN);
		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.0f);
		EGraphicCore::batch->draw_rect(place_x, place_y, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();

		glBlendEquation(GL_MAX);
		EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
		EGraphicCore::batch->draw_rect(place_x, place_y, EGraphicCore::last_texture_w, EGraphicCore::last_texture_h);
		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();

		//std::cout << "draw to x=" << place_x << " y=" << place_y << std::endl;

		new_gabarite = new EGabarite(_name, place_x / _ta->size_x, place_y / _ta->size_y, EGraphicCore::last_texture_w / _ta->size_x, EGraphicCore::last_texture_h / _ta->size_y);

		EGraphicCore::gabarite_list.push_back(new_gabarite);
	}
	else
	{
		//std::cout << "DUBLICATE <" << _name << ">" << std::endl;
		new_gabarite = duplicate_gabarite;
	}

	//load_texture(_path, 0);

	//set atlas texture is active
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//return normal blend mode
	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);

	//--------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------

	//cout << (int)01.35f << endl;

	//return normal viewport
	glViewport(0, 0, EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT);

	//active main texture

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _ta->colorbuffer);

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, _ta->colorbuffer);

	EGraphicCore::ourShader->setInt("texture1", 0);
	//EGraphicCore::ourShader->setInt("texture2", 1);

	EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);

	return new_gabarite;
}

void ETextureAtlas::draw_to_this_FBO(ETextureAtlas* _ta, ETextureAtlas* _ta2)
{
	glViewport(0, 0, _ta->size_x, _ta->size_y);
	glBindFramebuffer(GL_FRAMEBUFFER, _ta->framebuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _ta2->colorbuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//

	EGraphicCore::ourShader->setInt("texture1", 0);
}

void ETextureAtlas::active_this_texture_atlas(ETextureAtlas* _ta, ETextureAtlas* _ta2, ETextureAtlas* _ta3)
{
	glViewport(0, 0, _ta->size_x, _ta->size_y);
	glBindFramebuffer(GL_FRAMEBUFFER, _ta->framebuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _ta2->colorbuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//

	EGraphicCore::ourShader->setInt("texture1", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _ta3->colorbuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//

	EGraphicCore::ourShader->setInt("texture2", 1);
}

void ETextureAtlas::set_this_FBO_as_active(ETextureAtlas* _ta)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//return normal blend mode
	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);

	glViewport(0, 0, EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT);

	//active main texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _ta->colorbuffer);
	EGraphicCore::ourShader->setInt("texture1", 0);
	EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
}

ETextureAtlas::ETextureAtlas(int _x, int _y, int _color_depth, int _byte_mode)
{
	size_x = _x;
	size_y = _y;

	for (int j = 0; j < 1024; j++)
	for (int i = 0; i < 1024; i++)
	{
		free_space[j][i] = true;
	}

	//glGenTextures(1, &ETexture::texture[1]);

	//////////////////////////////
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &colorbuffer);
	glBindTexture(GL_TEXTURE_2D, colorbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, _color_depth, _x, _y, 0, GL_RGBA, _byte_mode, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorbuffer, 0);
	
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//////////////////////////////////////

	glViewport(0, 0, EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EGraphicCore::texture[0]);
	EGraphicCore::ourShader->setInt("texture1", 0);
	EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
}

ETextureAtlas::~ETextureAtlas()
{
}

EGabarite* ETextureAtlas::get_supermap_from_regular_texture_path(std::string _s, ETextureAtlas* _a)
{
	FILE* file;
	errno_t err;
	//								name			".png" is 4 char
	std::string path_to_supermap = _s.substr(0, _s.length() - 4) + "#supermap.png";

	if (err = fopen_s(&file, path_to_supermap.c_str(), "r") == 0)
	{
		err = fclose(file);

		//logger(path_to_supermap + " exist");
		return ETextureAtlas::put_texture_to_atlas(path_to_supermap, _a);
	}
	else
	{
		//logger(path_to_supermap + " not exist");
		return EGraphicCore::gabarite_supermap_placeholder;
	}
}

EGabarite* ETextureAtlas::get_normal_gloss_map_from_regular_texture_path(std::string _s, ETextureAtlas* _a)
{
	FILE* file;
	errno_t err;
	//								name			".png" is 4 char
	std::string path_to_normal_gloss_map = _s.substr(0, _s.length() - 4) + "#normal_gloss_map.png";

	if (err = fopen_s(&file, path_to_normal_gloss_map.c_str(), "r") == 0)
	{
		err = fclose(file);

		//logger(path_to_supermap + " exist");
		return ETextureAtlas::put_texture_to_atlas(path_to_normal_gloss_map, _a);
	}
	else
	{
		std::cout << _s << " not exist" << std::endl;
		//return EGraphicCore::gabarite_white_pixel;
		return ETextureAtlas::put_texture_to_atlas("data/textures/normal_gloss_placeholder.png", _a);
	}
}
