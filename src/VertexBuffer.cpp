#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(Primitive& primitive, unsigned int positionAttributeNumber, unsigned int positionDimensions, unsigned int colorAttributeNumber, unsigned int colorDimensions, unsigned int textureAttributeNumber, unsigned int textureDimensions){
	glGenBuffers(1, &this->vboID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, primitive.getDataSize(), primitive.getData(), GL_STATIC_DRAW);
	if (primitive.getIsIndexed()) {
		this->indexBuffer = new IndexBuffer(primitive.getIndices(), primitive.getIndicesSize());
	}
	glEnableVertexAttribArray(positionAttributeNumber);
	glVertexAttribPointer(positionAttributeNumber, positionDimensions, GL_FLOAT, GL_FALSE, (positionDimensions + colorDimensions + textureDimensions) * sizeof(float), (void*)0);
	glEnableVertexAttribArray(colorAttributeNumber);
	glVertexAttribPointer(colorAttributeNumber, colorDimensions, GL_FLOAT, GL_FALSE, (positionDimensions + colorDimensions + textureDimensions) * sizeof(float), (void*)(positionDimensions * sizeof(float)));
	glEnableVertexAttribArray(textureAttributeNumber);
	glVertexAttribPointer(textureAttributeNumber, textureDimensions, GL_FLOAT, GL_FALSE, (positionDimensions + colorDimensions + textureDimensions) * sizeof(float), (void*)((positionDimensions + colorDimensions) * sizeof(float)));
}
VertexBuffer::~VertexBuffer() {
	if(this->indexBuffer != nullptr){
		delete this->indexBuffer;
	}
}
void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
}
void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}