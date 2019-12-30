/**
* @file daeexport.h
* @brief A system which allows saving in-world objects to Collada .DAE files for offline texturizing/shading.
* @authors Latif Khalifa
*
* $LicenseInfo:firstyear=2013&license=LGPLV2.1$
* Copyright (C) 2013 Latif Khalifa
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General
* Public License along with this library; if not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301 USA
*/

#ifndef DAEEXPORT_H_
#define DAEEXPORT_H_

#include <dom/domElements.h>
#include "lltextureentry.h"
#include "lljoint.h"

class LLViewerObject;

class DAESaver
{
public:
	class MaterialInfo
	{
	public:
		LLUUID textureID;
		LLColor4 color;
		std::string name;

		bool matches(LLTextureEntry* te)
		{
			return (textureID == te->getID()) && (color == te->getColor());
		}

		bool operator== (const MaterialInfo& rhs)
		{
			return (textureID == rhs.textureID) && (color == rhs.color) && (name == rhs.name);
		}

		bool operator!= (const MaterialInfo& rhs)
		{
			return !(*this == rhs);
		}

		MaterialInfo()
		{
		}

		MaterialInfo(const MaterialInfo& rhs)
		{
			textureID = rhs.textureID;
			color = rhs.color;
			name = rhs.name;
		}

		MaterialInfo& operator= (const MaterialInfo& rhs)
		{
			textureID = rhs.textureID;
			color = rhs.color;
			name = rhs.name;
			return *this;
		}

	};

	typedef std::vector<std::pair<LLViewerObject*,std::string> > obj_info_t;
	typedef uuid_vec_t id_list_t;
	typedef std::vector<std::string> string_list_t;
	typedef std::vector<S32> int_list_t;
	typedef std::vector<MaterialInfo> material_list_t;

	material_list_t mAllMaterials;
	id_list_t mTextures;
	string_list_t mTextureNames;
	obj_info_t mObjects;
	LLMatrix4 mRootWorldInvMatrix;
	std::string mImageFormat;
	S32 mTotalNumMaterials;

	DAESaver();
	void updateTextureInfo();
	void add(const LLViewerObject* prim, const std::string name);
	bool saveDAE(std::string filename);

private:
	void transformTexCoord(S32 num_vert, LLVector2* coord, LLVector3* positions, LLVector3* normals, LLTextureEntry* te, LLVector3 scale);
	void addSourceParams(daeElement* mesh, const char* src_id, std::string params, const std::vector<F32>& vals);
	void addSource(daeElement* mesh, const char* src_id, const char* param_name, const std::vector<F32>& vals);
	void addSource(daeElement* parent, const char* src_id, const char* param_name, const std::vector<LLMatrix4>& vals);
	void addSource(daeElement* parent, const char* src_id, const char* param_name, const std::vector<std::string> &vals);
	void append(daeTArray<domFloat>& arr, const LLMatrix4& matrix);
	void addPolygons(daeElement* mesh, const char* geomID, const char* materialID, LLViewerObject* obj, int_list_t* faces_to_include);
	void addJointsAndWeights(daeElement* skin, const char* geomID, LLViewerObject* obj, int_list_t* faces_to_include);
	void addJointNodes(daeElement* parent, LLJoint* root);
	//void addJointNodes(daeElement* parent, LLJoint* root, LLMatrix4 transform_matrix);
	bool skipFace(LLTextureEntry *te);
	MaterialInfo getMaterial(LLTextureEntry* te);
	void getMaterials(LLViewerObject* obj, material_list_t* ret);
	void getFacesWithMaterial(LLViewerObject* obj, MaterialInfo& mat, int_list_t* ret);
	void generateEffects(daeElement *effects);
	void generateImagesSection(daeElement* images);
};

#endif // DAEEXPORT_H_

