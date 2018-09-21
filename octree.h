/*

Implementations of Octree member functions.

Copyright (C) 2011  Tao Ju

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
(LGPL) as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifndef		OCTREE_H
#define		OCTREE_H

#include "qef.h"

#include <vector>

#include <vector>
#include <utility>

#include <mathutils.h>

typedef float (*DistanceFunction)( const mu::Vec3 &, void * );

enum OctreeNodeType
{
	Node_None,
	Node_Internal,
	Node_Psuedo,
	Node_Leaf,
};


struct OctreeDrawInfo 
{
	OctreeDrawInfo()
		: index(-1)
		, corners(0)
	{
	}

	int				index;
	int				corners;
	mu::Vec3			position;
	mu::Vec3			averageNormal;
	svd::QefData	qef;
};



class OctreeNode
{
public:

	OctreeNode()
		: type(Node_None)
		, min(0, 0, 0)
		, size(0)
		, drawInfo(nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			children[i] = nullptr;
		}
	}

	OctreeNode(const OctreeNodeType _type)
		: type(_type)
		, min(0, 0, 0)
		, size(0)
		, drawInfo(nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			children[i] = nullptr;
		}
	}

	OctreeNodeType	type;
	mu::Vec3 		min;
	int				size;
	OctreeNode*		children[8];
	OctreeDrawInfo* drawInfo;
};

OctreeNode* BuildOctree(const mu::Vec3 & min, const int size, const float threshold, DistanceFunction f, void * data );
void DestroyOctree(OctreeNode* node);
void GenerateMeshFromOctree( OctreeNode* node, std::vector< std::pair< mu::Vec3, mu::Vec3 > > & vertexBuffer, std::vector< int > & indexBuffer );

#endif	// OCTREE_H

