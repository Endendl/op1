#pragma once
#ifndef MESH_H
#define MESH_H
#define MAX_BONE_INFLUENCE 4
#include "animdata.h"
#include "init_tool.h"
class mesh :
	public mounting
{
public:
	mesh() {};
	~mesh() {};
	struct Vertex 
	{
		glm::vec3 Position;//位置
		glm::vec3 Normal;//法相
		glm::vec2 TexCoords;//uv
		glm::vec3 Tangent;//正切
		glm::vec3 Bitangent;//双切
		int m_BoneIDs[MAX_BONE_INFLUENCE];//骨骼
		float m_Weights[MAX_BONE_INFLUENCE];//权重
	};
	bool setPosition = true;
	bool setNormal = true;
	bool setTexCoords = true;
	bool setTangent = false;
	bool setBitangent = false;
	bool setm_BoneIDs = false;
	bool setm_Weights = false;
	opengl_shader* mesh_shader;
	struct Texture
	{
		float shininess;
		unsigned int ID;
		std::string type;
		std::string path;//// 我们储存纹理的路径用于与其它纹理进行比较

	};
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;
	
	/*  函数  */
	//void Draw(opengl_shader& shader) {
	void Draw() override{
		opengl_shader* shader = gameobjct->thisshader;
	//void Draw(opengl_shader* shader, glm::vec3 _Position) {
		unsigned int diffuseNr = 0;
		unsigned int specularNr = 0;
		unsigned int normalNr = 0;
		unsigned int heightNr = 0;

		shader->use();

		glm::mat4 model = glm::mat4(1.0f);
		
		model = glm::translate(model, gameobjct->transform.Position);
		model = glm::rotate(model, glm::radians(gameobjct->transform.rotate.x), glm::vec3(1.0,0,0));
		model = glm::rotate(model, glm::radians(gameobjct->transform.rotate.y), glm::vec3(0,1.0,0));
		model = glm::rotate(model, glm::radians(gameobjct->transform.rotate.z), glm::vec3(0,0,1.0));
		model = glm::scale(model, gameobjct->transform.Scale);
		//model = glm::translate(model, gameobjct->transform.Position);
		shader->setMat4("model", model);
		//std::cout << "name" << gameobjct->name << std::endl;
		//std::cout << "x" << gameobjct->transform.Position.x << "y" << gameobjct->transform.Position.y << "z" << gameobjct->transform.Position.z << std::endl;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); 
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse") {
				//glActiveTexture(GL_TEXTURE0);
				number = std::to_string(diffuseNr++);

			}
			else if (name == "texture_specular") {
				//glActiveTexture(GL_TEXTURE1);
				number = std::to_string(specularNr++); 
			}
			else if (name == "texture_normal") {
				//glActiveTexture(GL_TEXTURE2);
				number = std::to_string(normalNr++); 
			}
			else if (name == "texture_height") {
				//glActiveTexture(GL_TEXTURE3);
				number = std::to_string(heightNr++); 
			}
			shader->setInt(("material." + name + "[" + number + "]").c_str(), i);
			shader->setFloat("material.shininess", textures[i].shininess);
			glBindTexture(GL_TEXTURE_2D, textures[i].ID);
		}
		//std::cout << "Drawing with shader: " << shader.name << " (ID: " << shader.ID << ")\n";
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
	};
	mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
		this->vertices = vertices;
		this->textures = textures;
		this->indices = indices;
		setupMesh();

	};
	mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, bool _setPosition, bool _setNorma, bool _setTexCoords, bool _setTangent, bool _setBitangent, bool _setm_BoneIDs, bool _setm_Weights) {
		this->vertices = vertices;
		this->textures = textures;
		this->indices = indices;
		this->setPosition = _setPosition;
		this->setNormal = _setNorma;
		this->setTexCoords = _setTexCoords;
		this->setTangent = _setTangent;
		this->setBitangent = _setBitangent;
		this->setm_BoneIDs = _setm_BoneIDs;
		this->setm_Weights = _setm_Weights;
		setupMesh();
	};
	mesh(float vertices[]) {
		this->vertices.resize(36);
		memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));
		setupMesh();

	};
private:
	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;
	/*  函数  */
	void setupMesh() {
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓冲方式
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//重新计算使用的部分所占的内存长度
		//int Vertexsize = ((int)setPosition + (int)setNormal + (int)setTangent + (int)setBitangent) * sizeof(glm::vec3) + setTexCoords * sizeof(glm::vec2) + setm_BoneIDs * sizeof(int[MAX_BONE_INFLUENCE]) + setm_Weights * sizeof(float[MAX_BONE_INFLUENCE]);
		int Vertexsize = sizeof(Vertex);
		//vao

		//std::cout << "\nVertexsize: " << Vertexsize << "\tVertex: " << sizeof(Vertex) << std::endl;
		//记录偏移量//只记录已使用部分偏移量
		int Vertexsizecontinue = 0;
		//顶点坐标数据
		if (setPosition) {
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertexsize, (void*)0);
			Vertexsizecontinue += sizeof(glm::vec3);
		}
		// 顶点法线
		if (setNormal) {
			glEnableVertexAttribArray(1);
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertexsize, (void*)offsetof(Vertex, Normal));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertexsize, (void*)Vertexsizecontinue);
			//std::cout << "\n(void*)offsetof(Vertex, Normal): " << offsetof(Vertex, Normal) << "\tVertexsizecontinue: " << Vertexsizecontinue << std::endl;
			Vertexsizecontinue += sizeof(glm::vec3);
		}
		// 顶点纹理坐标
		if (setTexCoords) {
			glEnableVertexAttribArray(2);
			//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Vertexsize, (void*)offsetof(Vertex, TexCoords));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Vertexsize, (void*)Vertexsizecontinue);
			//std::cout << "\n(void*)offsetof(Vertex, TexCoords): " << offsetof(Vertex, TexCoords) << "\tVertexsizecontinue: " << Vertexsizecontinue << std::endl;
			Vertexsizecontinue += sizeof(glm::vec2);
		}
		if (setTangent) {
			glEnableVertexAttribArray(3);
			//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, Vertexsize, (void*)offsetof(Vertex, Tangent));
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, Vertexsize, (void*)Vertexsizecontinue);
			//std::cout << "\n(void*)offsetof(Vertex, setTangent): " << offsetof(Vertex, Tangent) << "\tVertexsizecontinue: " << Vertexsizecontinue << std::endl;
			Vertexsizecontinue += sizeof(glm::vec3);
		}
		// vertex bitangent
		if (setBitangent) {
			glEnableVertexAttribArray(4);
			//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, Vertexsize, (void*)offsetof(Vertex, Bitangent));
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, Vertexsize, (void*)Vertexsizecontinue);
			//std::cout << "\n(void*)offsetof(Vertex, setBitangent): " << offsetof(Vertex, Bitangent) << "\tVertexsizecontinue: " << Vertexsizecontinue << std::endl;
			Vertexsizecontinue += sizeof(glm::vec3);
		}
		// ids
		if (setm_BoneIDs) {
			glEnableVertexAttribArray(5);
			//glVertexAttribIPointer(5, 4, GL_INT, Vertexsize, (void*)offsetof(Vertex, m_BoneIDs));
			glVertexAttribIPointer(5, 4, GL_INT, Vertexsize, (void*)Vertexsizecontinue);
			//std::cout << "\n(void*)offsetof(Vertex, setm_BoneIDs): " << offsetof(Vertex, m_BoneIDs) << "\tVertexsizecontinue: " << Vertexsizecontinue << std::endl;
			Vertexsizecontinue += sizeof(int) * 4;
		}
		// weights
		if (setm_Weights) {
			glEnableVertexAttribArray(6);
			//glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, Vertexsize, (void*)offsetof(Vertex, m_Weights));
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, Vertexsize, (void*)Vertexsizecontinue);
			//std::cout << "\n(void*)offsetof(Vertex, setm_Weights): " << offsetof(Vertex, m_Weights) << "\tVertexsizecontinue: " << Vertexsizecontinue << std::endl;
			Vertexsizecontinue += sizeof(float) * 4;
		}
		//std::cout << "mesh: " << sizeof(Vertex);


		glBindVertexArray(0);
	};
};
class meshlist :
	public mounting {
public:
	meshlist(GameObject* _obj, std::string _path) {
		this->gameobjct = _obj;
		loadmodel(_path);
		std::string tmppath = _path;
		// 找到最后一个反斜杠的位置
		size_t lastSlashPos = tmppath.find_last_of("\\");
		//gameobjct->Darwmountinglist.push_back(this);
		// 提取文件名
		//name = tmppath.substr(0, (tmppath.find_last_of("."))).substr(lastSlashPos + 1);
		//PATH = PATH.substr(0, (PATH.find_last_of("\\")));
		//std::cout << name << std::endl;
	}
	void Draw() override {
		//std::cout << "模型内" << shader.ID;
		//for (int i = 0; i < meshes.size(); i++)
		//{
		//	meshes[i].Draw(*gameobjct->thisshader);
		//}
	};

	

private:
	std::vector<mesh::Texture> textures_loaded;//我们希望将纹理的路径与储存在textures_loaded这个vector中的所有纹理进行比较，看看当前纹理的路径是否与其中的一个相同。如果是的话，则跳过纹理加载/生成的部分，直接使用定位到的纹理结构体为网格的纹理。更新后的函数如下：
	//std::vector<mesh> meshes;
	std::string directory;
	std::map<std::string, BoneInfo> m_BoneInfoMap; //
	int m_BoneCounter = 0;

	void SetVertexBoneDataToDefault(mesh::Vertex& _vertex)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
		{
			_vertex.m_BoneIDs[i] = -1;  // 将骨骼 ID 设置为无效值
			_vertex.m_Weights[i] = 0.0f; // 将权重设置为 0
		}
	}

	void SetVertexBoneData(mesh::Vertex& _vertex, int _boneID, float _weight)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
		{
			if (_vertex.m_BoneIDs[i] < 0) // 找到第一个未使用的插槽
			{
				_vertex.m_Weights[i] = _weight; // 设置权重
				_vertex.m_BoneIDs[i] = _boneID; // 设置骨骼 ID
				break; // 完成设置，退出循环
			}
		}
	}

	void ExtractBoneWeightForVertices(std::vector<mesh::Vertex>& vertices, aiMesh* mesh, const aiScene* scene)//骨骼信息的提取和顶点权重的设置
	{
		for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
		{
			int boneID = -1;
			std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();

			// 检查骨骼是否已经存在于 BoneInfoMap 中
			if (m_BoneInfoMap.find(boneName) == m_BoneInfoMap.end())
			{
				// 如果不存在，则创建一个新的 BoneInfo
				BoneInfo newBoneInfo;
				newBoneInfo.id = m_BoneCounter;
				newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(
					mesh->mBones[boneIndex]->mOffsetMatrix);
				m_BoneInfoMap[boneName] = newBoneInfo;
				boneID = m_BoneCounter;
				m_BoneCounter++;
			}
			else
			{
				// 如果存在，则直接获取其 ID
				boneID = m_BoneInfoMap[boneName].id;
			}

			// 确保 boneID 有效
			assert(boneID != -1);

			// 获取骨骼的权重信息
			auto weights = mesh->mBones[boneIndex]->mWeights;
			int numWeights = mesh->mBones[boneIndex]->mNumWeights;

			// 遍历权重信息，应用到对应的顶点
			for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
			{
				int vertexId = weights[weightIndex].mVertexId;
				float weight = weights[weightIndex].mWeight;

				// 确保顶点 ID 有效
				if (vertexId >= vertices.size()) {
					std::cerr << "Error: vertexId " << vertexId << " is out of bounds (vertices size: " << vertices.size() << ")" << std::endl;
					continue; // 跳过无效的顶点 ID
				}

				//// 确保顶点 ID 有效
				//assert(vertexId < vertices.size());

				// 设置顶点的骨骼数据
				SetVertexBoneData(vertices[vertexId], boneID, weight);
			}
		}
	}

	void loadmodel(std::string _path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		//const aiScene* scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // 如果scene不为空
		{
			std::cout << "\n模型ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		directory = _path.substr(0, _path.find_last_of('\\'));
		//std::cout << directory << std::endl;
		// process ASSIMP's root node recursively
		processNode(scene->mRootNode, scene);
	}
	void processNode(aiNode* node, const aiScene* scene) {
		//std::cout << node->mName.data << "\n";
		// 处理节点所有的网格（如果有的话）
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* tempmesh = scene->mMeshes[node->mMeshes[i]];
			mountingadd(gameobjct, new mesh(processMesh(tempmesh, scene)));
			gameobjct->Drawmountinglist.push_back(gameobjct->mountinglist[gameobjct->mountinglist.size() - 1]);

			gameobjct->Drawmountinglist.back()->name = node->mName.data;
		}
		// 接下来对它的子节点重复这一过程 递归深度搜索
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}
	mesh processMesh(aiMesh* _mesh, const aiScene* scene) {
		std::vector<mesh::Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<mesh::Texture> textures;

		bool setPosition = false;
		bool setNormal = false;
		bool setTexCoords = false;
		bool setTangent = false;
		bool setBitangent = false;
		bool setm_BoneIDs = true;
		bool setm_Weights = true;
		//网格
		for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
		{
			mesh::Vertex tempVertex;
			SetVertexBoneDataToDefault(tempVertex);

			//tempVertex.Position = glm::vec3(_mesh->mVertices[i].x, _mesh->mVertices[i].y, _mesh->mVertices[i].z);
			tempVertex.Position = AssimpGLMHelpers::GetGLMVec(_mesh->mVertices[i]);
			//tempVertex.Position = glm::vec3(_mesh->mVertices[i].x, _mesh->mVertices[i].y, _mesh->mVertices[i].z);
			setPosition = true;
			if (_mesh->HasNormals())//向量
			{
				//tempVertex.Normal = glm::vec3(_mesh->mNormals[i].x, _mesh->mNormals[i].y, _mesh->mNormals[i].z);
				tempVertex.Normal = AssimpGLMHelpers::GetGLMVec(_mesh->mNormals[i]);
				setNormal = true;
			}
			if (_mesh->mTextureCoords[0]) //读uv
			{
				tempVertex.TexCoords = glm::vec2(_mesh->mTextureCoords[0][i].x, _mesh->mTextureCoords[0][i].y);
				setTexCoords = true;
				if (_mesh->HasTangentsAndBitangents()) {
					// tangent
					tempVertex.Tangent = glm::vec3(_mesh->mTangents[i].x, _mesh->mTangents[i].y, _mesh->mTangents[i].z);
					// bitangent
					tempVertex.Bitangent = glm::vec3(_mesh->mBitangents[i].x, _mesh->mBitangents[i].y, _mesh->mBitangents[i].z);
					setTangent = true;
					setBitangent = true;
				}
			}
			else {
				tempVertex.TexCoords = glm::vec2(0.0f, 0.0f);
				setTexCoords = true;
			}


			vertices.push_back(tempVertex);

		}

		//索引
		for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
		{
			aiFace face = _mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int i2 = 0; i2 < face.mNumIndices; i2++)
				indices.push_back(face.mIndices[i2]);
		}

		aiMaterial* material = scene->mMaterials[_mesh->mMaterialIndex];

		// 1. diffuse maps 抓取各种材质
		std::vector<mesh::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");//函数遍历了给定纹理类型的所有纹理位置，获取了纹理的文件位置，并加载并和生成了纹理，将信息储存在了一个Vertex结构体中
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<mesh::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<mesh::Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		std::vector<mesh::Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		mesh tempmesh(vertices, indices, textures, setPosition, setNormal, setTexCoords, setTangent, setBitangent, setm_BoneIDs, setm_Weights);
		tempmesh.gameobjct = gameobjct;

		ExtractBoneWeightForVertices(vertices, _mesh, scene);

		return tempmesh;
		//return mesh::mesh(vertices, indices, textures, 1, 1, 1, setTangent, setBitangent);
	}
	std::vector<mesh::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)//函数遍历了给定纹理类型的所有纹理位置，获取了纹理的文件位置，并加载并和生成了纹理，将信息储存在了一个Vertex结构体中
	{
		std::vector<mesh::Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;
			for (unsigned int i2 = 0; i2 < textures_loaded.size(); i2++)
			{
				if (std::strcmp(textures_loaded[i2].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[i2]);
					skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
					break;
				}
			}
			if (!skip)
			{   // 如果纹理还没有被加载，则加载它
				mesh::Texture texture;
				texture.ID = TextureFromFile(str.C_Str(), this->directory);
				texture.shininess = 32.0f;
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture);  // 添加到已加载的纹理中
			}
		}
		return textures;
	}

	unsigned int TextureFromFile(const char* path, const std::string& directory)
	{
		std::string filename = std::string(path);

		filename = directory + '\\' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "找不到纹理Texture failed to load at path: " << filename << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}


};


#endif