#include "EGraphicCore.h"




Batcher::Batcher()
{
	//zzz(indices_buffer);
	//indices_buffer = generateData();
}

Batcher::~Batcher()
{
}

void Batcher::draw_call()
{
	if (last_vertice_buffer_index > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * last_vertice_buffer_index, vertex_buffer, GL_DYNAMIC_DRAW);



		glDrawElements(GL_TRIANGLES, 6 * (last_vertice_buffer_index / 32), GL_UNSIGNED_INT, 0);
	}
}
