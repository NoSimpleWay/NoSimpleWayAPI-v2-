#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION 
#include "NoSimpleWayAPI[v2]/EGraphicCore.h"
#include "NoSimpleWayAPI[v2]/EInputCore.h"
#include "NoSimpleWayAPI[v2]/EGUICore.h"
#include "EWindowMain.h"


//extern GLFWwindow* main_window{ nullptr };



int main()
{
	

// glfw window creation
// --------------------


	NS_EGraphicCore::initiate_graphic_core();
	EInputCore::initiate_input_core();

	
	
	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);
	//logger_param("max_texture_size:", max_tex_size);

	glfwSwapInterval(1);


			
			NS_EGraphicCore::default_batcher_for_drawing->set_transform_screen_size
			(
				NS_EGraphicCore::SCREEN_WIDTH,
				NS_EGraphicCore::SCREEN_HEIGHT
			);



		//ETextureGabarite* gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);
		//gudron = NS_EGraphicCore::put_texture_to_atlas("data/textures/gudron_roof.png", NS_EGraphicCore::default_texture_atlas);


		//EGraphicCore::shader_texture_atlas_putter->setInt("texture1", 0);
		NS_EGraphicCore::default_batcher_for_drawing->set_color(NS_EColorCollection::COLOR_WHITE);


		EWindowMain::link_to_main_window = new EWindowMain();
		EWindow::window_list.push_back(EWindowMain::link_to_main_window);

	while (!glfwWindowShouldClose(NS_EGraphicCore::main_window))
	{


		clock_t time = clock();

		NS_EGraphicCore::delta_time = (time - NS_EGraphicCore::saved_time_for_delta) / 1000.0;
		NS_EGraphicCore::saved_time_for_delta = time;

		

		glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();



		NS_EGraphicCore::gl_set_texture_filtering(GL_CLAMP_TO_EDGE, GL_LINEAR);
		NS_EGraphicCore::gl_set_blend_mode_default();
		
		
		for (EWindow* w : EWindow::window_list)
		{
			w->update_default(NS_EGraphicCore::delta_time);
			w->update_additional(NS_EGraphicCore::delta_time);

			w->GUI_update_default(NS_EGraphicCore::delta_time);
			w->GUI_update_additional(NS_EGraphicCore::delta_time);
		}

		for (EWindow* w : EWindow::window_list)
		{
			w->draw_default(NS_EGraphicCore::delta_time);
			w->draw_additional(NS_EGraphicCore::delta_time);

			w->GUI_draw_default(NS_EGraphicCore::delta_time);
			w->GUI_draw_additional(NS_EGraphicCore::delta_time);
		}
		

		glfwSwapBuffers(NS_EGraphicCore::main_window);

		EInputCore::LAST_INPUTED_CHAR	=	NULL;
		EInputCore::scroll_direction	=	0;
	}

	return 0;

}