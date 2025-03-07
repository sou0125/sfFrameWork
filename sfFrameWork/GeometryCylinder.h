#pragma once
#include "Geometry.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace sf
{
	namespace geometry
	{
		//�`��N���X-�~��
		class GeometryCylinder :public Geometry
		{
		public:
			GeometryCylinder();

			void Draw(const Material& mtl)override;

		private:
			dx::VertexBuffer<dx::Vertex3D> vertexBuffer;
			dx::IndexBuffer indexBuffer;

			const static int segments = 16;
			const static int longitudeSegments = 16;
		};
	}
}