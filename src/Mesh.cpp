#include "Mesh.hpp"

Mesh::Mesh() {
	HRESULT guidResult = CoCreateGuid(&this->id);
	this->name = "";
	this->vertexArray = nullptr;
	this->vertexBuffer = nullptr;
	this->primitive = nullptr;
}


Mesh::Mesh(Primitive& primitive, std::string name, int positionAttributeNumber, int positionDimensions, int colorAttributeNumber, int colorDimensions, int textureAttributeNumber, int textureDimensions) {
	HRESULT guidResult = CoCreateGuid(&this->id);
	this->name = name;
	this->primitive = new Primitive(primitive);
	this->vertexArray = new VertexArray();
	this->vertexArray->bind();
	this->vertexBuffer = new VertexBuffer(
		*this->primitive,
		positionAttributeNumber,
		positionDimensions,
		colorAttributeNumber,
		colorDimensions,
		textureAttributeNumber,
		textureDimensions);
	this->vertexArray->unbind();

}

Mesh::~Mesh(){
	delete this->vertexArray;
	delete this->vertexBuffer;
	delete this->primitive;
}