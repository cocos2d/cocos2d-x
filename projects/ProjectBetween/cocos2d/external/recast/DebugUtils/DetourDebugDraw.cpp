//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include "DebugDraw.h"
#include "DetourDebugDraw.h"
#include "recast/Detour/DetourNavMesh.h"
#include "recast/Detour/DetourCommon.h"
#include "recast/Detour/DetourNode.h"


static float distancePtLine2d(const float* pt, const float* p, const float* q)
{
	float pqx = q[0] - p[0];
	float pqz = q[2] - p[2];
	float dx = pt[0] - p[0];
	float dz = pt[2] - p[2];
	float d = pqx*pqx + pqz*pqz;
	float t = pqx*dx + pqz*dz;
	if (d != 0) t /= d;
	dx = p[0] + t*pqx - pt[0];
	dz = p[2] + t*pqz - pt[2];
	return dx*dx + dz*dz;
}

static void drawPolyBoundaries(duDebugDraw* dd, const dtMeshTile* tile,
							   const unsigned int col, const float linew,
							   bool inner)
{
	static const float thr = 0.01f*0.01f;

	dd->begin(DU_DRAW_LINES, linew);

	for (int i = 0; i < tile->header->polyCount; ++i)
	{
		const dtPoly* p = &tile->polys[i];
		
		if (p->getType() == DT_POLYTYPE_OFFMESH_CONNECTION) continue;
		
		const dtPolyDetail* pd = &tile->detailMeshes[i];
		
		for (int j = 0, nj = (int)p->vertCount; j < nj; ++j)
		{
			unsigned int c = col;
			if (inner)
			{
				if (p->neis[j] == 0) continue;
				if (p->neis[j] & DT_EXT_LINK)
				{
					bool con = false;
					for (unsigned int k = p->firstLink; k != DT_NULL_LINK; k = tile->links[k].next)
					{
						if (tile->links[k].edge == j)
						{
							con = true;
							break;
						}
					}
					if (con)
						c = duRGBA(255,255,255,48);
					else
						c = duRGBA(0,0,0,48);
				}
				else
					c = duRGBA(0,48,64,32);
			}
			else
			{
				if (p->neis[j] != 0) continue;
			}
			
			const float* v0 = &tile->verts[p->verts[j]*3];
			const float* v1 = &tile->verts[p->verts[(j+1) % nj]*3];
			
			// Draw detail mesh edges which align with the actual poly edge.
			// This is really slow.
			for (int k = 0; k < pd->triCount; ++k)
			{
				const unsigned char* t = &tile->detailTris[(pd->triBase+k)*4];
				const float* tv[3];
				for (int m = 0; m < 3; ++m)
				{
					if (t[m] < p->vertCount)
						tv[m] = &tile->verts[p->verts[t[m]]*3];
					else
						tv[m] = &tile->detailVerts[(pd->vertBase+(t[m]-p->vertCount))*3];
				}
				for (int m = 0, n = 2; m < 3; n=m++)
				{
					if (((t[3] >> (n*2)) & 0x3) == 0) continue;	// Skip inner detail edges.
					if (distancePtLine2d(tv[n],v0,v1) < thr &&
						distancePtLine2d(tv[m],v0,v1) < thr)
					{
						dd->vertex(tv[n], c);
						dd->vertex(tv[m], c);
					}
				}
			}
		}
	}
	dd->end();
}

static void drawMeshTile(duDebugDraw* dd, const dtNavMesh& mesh, const dtNavMeshQuery* query,
						 const dtMeshTile* tile, unsigned char flags)
{
	dtPolyRef base = mesh.getPolyRefBase(tile);

	int tileNum = mesh.decodePolyIdTile(base);
	
	dd->depthMask(false);

	dd->begin(DU_DRAW_TRIS);
	for (int i = 0; i < tile->header->polyCount; ++i)
	{
		const dtPoly* p = &tile->polys[i];
		if (p->getType() == DT_POLYTYPE_OFFMESH_CONNECTION)	// Skip off-mesh links.
			continue;
			
		const dtPolyDetail* pd = &tile->detailMeshes[i];

		unsigned int col;
		if (query && query->isInClosedList(base | (dtPolyRef)i))
			col = duRGBA(255,196,0,64);
		else
		{
			if (flags & DU_DRAWNAVMESH_COLOR_TILES)
			{
				col = duIntToCol(tileNum, 128);
			}
			else
			{
				if (p->getArea() == 0) // Treat zero area type as default.
					col = duRGBA(0,192,255,64);
				else
					col = duIntToCol(p->getArea(), 64);
			}
		}
		
		for (int j = 0; j < pd->triCount; ++j)
		{
			const unsigned char* t = &tile->detailTris[(pd->triBase+j)*4];
			for (int k = 0; k < 3; ++k)
			{
				if (t[k] < p->vertCount)
					dd->vertex(&tile->verts[p->verts[t[k]]*3], col);
				else
					dd->vertex(&tile->detailVerts[(pd->vertBase+t[k]-p->vertCount)*3], col);
			}
		}
	}
	dd->end();
	
	// Draw inter poly boundaries
	drawPolyBoundaries(dd, tile, duRGBA(0,48,64,32), 1.5f, true);
	
	// Draw outer poly boundaries
	drawPolyBoundaries(dd, tile, duRGBA(0,48,64,220), 2.5f, false);

	if (flags & DU_DRAWNAVMESH_OFFMESHCONS)
	{
		dd->begin(DU_DRAW_LINES, 2.0f);
		for (int i = 0; i < tile->header->polyCount; ++i)
		{
			const dtPoly* p = &tile->polys[i];
			if (p->getType() != DT_POLYTYPE_OFFMESH_CONNECTION)	// Skip regular polys.
				continue;
			
			unsigned int col, col2;
			if (query && query->isInClosedList(base | (dtPolyRef)i))
				col = duRGBA(255,196,0,220);
			else
				col = duDarkenCol(duIntToCol(p->getArea(), 220));
			
			const dtOffMeshConnection* con = &tile->offMeshCons[i - tile->header->offMeshBase];
			const float* va = &tile->verts[p->verts[0]*3];
			const float* vb = &tile->verts[p->verts[1]*3];

			// Check to see if start and end end-points have links.
			bool startSet = false;
			bool endSet = false;
			for (unsigned int k = p->firstLink; k != DT_NULL_LINK; k = tile->links[k].next)
			{
				if (tile->links[k].edge == 0)
					startSet = true;
				if (tile->links[k].edge == 1)
					endSet = true;
			}
			
			// End points and their on-mesh locations.
			dd->vertex(va[0],va[1],va[2], col);
			dd->vertex(con->pos[0],con->pos[1],con->pos[2], col);
			col2 = startSet ? col : duRGBA(220,32,16,196);
			duAppendCircle(dd, con->pos[0],con->pos[1]+0.1f,con->pos[2], con->rad, col2);

			dd->vertex(vb[0],vb[1],vb[2], col);
			dd->vertex(con->pos[3],con->pos[4],con->pos[5], col);
			col2 = endSet ? col : duRGBA(220,32,16,196);
			duAppendCircle(dd, con->pos[3],con->pos[4]+0.1f,con->pos[5], con->rad, col2);
			
			// End point vertices.
			dd->vertex(con->pos[0],con->pos[1],con->pos[2], duRGBA(0,48,64,196));
			dd->vertex(con->pos[0],con->pos[1]+0.2f,con->pos[2], duRGBA(0,48,64,196));
			
			dd->vertex(con->pos[3],con->pos[4],con->pos[5], duRGBA(0,48,64,196));
			dd->vertex(con->pos[3],con->pos[4]+0.2f,con->pos[5], duRGBA(0,48,64,196));
			
			// Connection arc.
			duAppendArc(dd, con->pos[0],con->pos[1],con->pos[2], con->pos[3],con->pos[4],con->pos[5], 0.25f,
						(con->flags & 1) ? 0.6f : 0, 0.6f, col);
		}
		dd->end();
	}
	
	const unsigned int vcol = duRGBA(0,0,0,196);
	dd->begin(DU_DRAW_POINTS, 3.0f);
	for (int i = 0; i < tile->header->vertCount; ++i)
	{
		const float* v = &tile->verts[i*3];
		dd->vertex(v[0], v[1], v[2], vcol);
	}
	dd->end();

	dd->depthMask(true);
}

void duDebugDrawNavMesh(duDebugDraw* dd, const dtNavMesh& mesh, unsigned char flags)
{
	if (!dd) return;
	
	for (int i = 0; i < mesh.getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh.getTile(i);
		if (!tile->header) continue;
		drawMeshTile(dd, mesh, 0, tile, flags);
	}
}

void duDebugDrawNavMeshWithClosedList(struct duDebugDraw* dd, const dtNavMesh& mesh, const dtNavMeshQuery& query, unsigned char flags)
{
	if (!dd) return;

	const dtNavMeshQuery* q = (flags & DU_DRAWNAVMESH_CLOSEDLIST) ? &query : 0;
	
	for (int i = 0; i < mesh.getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh.getTile(i);
		if (!tile->header) continue;
		drawMeshTile(dd, mesh, q, tile, flags);
	}
}

void duDebugDrawNavMeshNodes(struct duDebugDraw* dd, const dtNavMeshQuery& query)
{
	if (!dd) return;
	
	const dtNodePool* pool = query.getNodePool();
	if (pool)
	{
		const float off = 0.5f;
		dd->begin(DU_DRAW_POINTS, 4.0f);
		for (int i = 0; i < pool->getHashSize(); ++i)
		{
			for (dtNodeIndex j = pool->getFirst(i); j != DT_NULL_IDX; j = pool->getNext(j))
			{
				const dtNode* node = pool->getNodeAtIdx(j+1);
				if (!node) continue;
				dd->vertex(node->pos[0],node->pos[1]+off,node->pos[2], duRGBA(255,192,0,255));
			}
		}
		dd->end();
		
		dd->begin(DU_DRAW_LINES, 2.0f);
		for (int i = 0; i < pool->getHashSize(); ++i)
		{
			for (dtNodeIndex j = pool->getFirst(i); j != DT_NULL_IDX; j = pool->getNext(j))
			{
				const dtNode* node = pool->getNodeAtIdx(j+1);
				if (!node) continue;
				if (!node->pidx) continue;
				const dtNode* parent = pool->getNodeAtIdx(node->pidx);
				if (!parent) continue;
				dd->vertex(node->pos[0],node->pos[1]+off,node->pos[2], duRGBA(255,192,0,128));
				dd->vertex(parent->pos[0],parent->pos[1]+off,parent->pos[2], duRGBA(255,192,0,128));
			}
		}
		dd->end();
	}
}


static void drawMeshTileBVTree(duDebugDraw* dd, const dtMeshTile* tile)
{
	// Draw BV nodes.
	const float cs = 1.0f / tile->header->bvQuantFactor;
	dd->begin(DU_DRAW_LINES, 1.0f);
	for (int i = 0; i < tile->header->bvNodeCount; ++i)
	{
		const dtBVNode* n = &tile->bvTree[i];
		if (n->i < 0) // Leaf indices are positive.
			continue;
		duAppendBoxWire(dd, tile->header->bmin[0] + n->bmin[0]*cs,
						tile->header->bmin[1] + n->bmin[1]*cs,
						tile->header->bmin[2] + n->bmin[2]*cs,
						tile->header->bmin[0] + n->bmax[0]*cs,
						tile->header->bmin[1] + n->bmax[1]*cs,
						tile->header->bmin[2] + n->bmax[2]*cs,
						duRGBA(255,255,255,128));
	}
	dd->end();
}

void duDebugDrawNavMeshBVTree(duDebugDraw* dd, const dtNavMesh& mesh)
{
	if (!dd) return;
	
	for (int i = 0; i < mesh.getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh.getTile(i);
		if (!tile->header) continue;
		drawMeshTileBVTree(dd, tile);
	}
}

static void drawMeshTilePortal(duDebugDraw* dd, const dtMeshTile* tile)
{
	// Draw portals
	const float padx = 0.04f;
	const float pady = tile->header->walkableClimb;

	dd->begin(DU_DRAW_LINES, 2.0f);

	for (int side = 0; side < 8; ++side)
	{
		unsigned short m = DT_EXT_LINK | (unsigned short)side;
		
		for (int i = 0; i < tile->header->polyCount; ++i)
		{
			dtPoly* poly = &tile->polys[i];
			
			// Create new links.
			const int nv = poly->vertCount;
			for (int j = 0; j < nv; ++j)
			{
				// Skip edges which do not point to the right side.
				if (poly->neis[j] != m)
					continue;
				
				// Create new links
				const float* va = &tile->verts[poly->verts[j]*3];
				const float* vb = &tile->verts[poly->verts[(j+1) % nv]*3];
				
				if (side == 0 || side == 4)
				{
					unsigned int col = side == 0 ? duRGBA(128,0,0,128) : duRGBA(128,0,128,128);

					const float x = va[0] + ((side == 0) ? -padx : padx);
					
					dd->vertex(x,va[1]-pady,va[2], col);
					dd->vertex(x,va[1]+pady,va[2], col);

					dd->vertex(x,va[1]+pady,va[2], col);
					dd->vertex(x,vb[1]+pady,vb[2], col);

					dd->vertex(x,vb[1]+pady,vb[2], col);
					dd->vertex(x,vb[1]-pady,vb[2], col);

					dd->vertex(x,vb[1]-pady,vb[2], col);
					dd->vertex(x,va[1]-pady,va[2], col);
				}
				else if (side == 2 || side == 6)
				{
					unsigned int col = side == 2 ? duRGBA(0,128,0,128) : duRGBA(0,128,128,128);

					const float z = va[2] + ((side == 2) ? -padx : padx);
					
					dd->vertex(va[0],va[1]-pady,z, col);
					dd->vertex(va[0],va[1]+pady,z, col);
					
					dd->vertex(va[0],va[1]+pady,z, col);
					dd->vertex(vb[0],vb[1]+pady,z, col);
					
					dd->vertex(vb[0],vb[1]+pady,z, col);
					dd->vertex(vb[0],vb[1]-pady,z, col);
					
					dd->vertex(vb[0],vb[1]-pady,z, col);
					dd->vertex(va[0],va[1]-pady,z, col);
				}

			}
		}
	}
	
	dd->end();
}

void duDebugDrawNavMeshPortals(duDebugDraw* dd, const dtNavMesh& mesh)
{
	if (!dd) return;
	
	for (int i = 0; i < mesh.getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh.getTile(i);
		if (!tile->header) continue;
		drawMeshTilePortal(dd, tile);
	}
}

void duDebugDrawNavMeshPolysWithFlags(struct duDebugDraw* dd, const dtNavMesh& mesh,
									  const unsigned short polyFlags, const unsigned int col)
{
	if (!dd) return;
	
	for (int i = 0; i < mesh.getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh.getTile(i);
		if (!tile->header) continue;
		dtPolyRef base = mesh.getPolyRefBase(tile);

		for (int j = 0; j < tile->header->polyCount; ++j)
		{
			const dtPoly* p = &tile->polys[j];
			if ((p->flags & polyFlags) == 0) continue;
			duDebugDrawNavMeshPoly(dd, mesh, base|(dtPolyRef)j, col);
		}
	}
}

void duDebugDrawNavMeshPoly(duDebugDraw* dd, const dtNavMesh& mesh, dtPolyRef ref, const unsigned int col)
{
	if (!dd) return;
	
	const dtMeshTile* tile = 0;
	const dtPoly* poly = 0;
	if (dtStatusFailed(mesh.getTileAndPolyByRef(ref, &tile, &poly)))
		return;
	
	dd->depthMask(false);
	
	const unsigned int c = (col & 0x00ffffff) | (64 << 24);
	const unsigned int ip = (unsigned int)(poly - tile->polys);

	if (poly->getType() == DT_POLYTYPE_OFFMESH_CONNECTION)
	{
		dtOffMeshConnection* con = &tile->offMeshCons[ip - tile->header->offMeshBase];

		dd->begin(DU_DRAW_LINES, 2.0f);

		// Connection arc.
		duAppendArc(dd, con->pos[0],con->pos[1],con->pos[2], con->pos[3],con->pos[4],con->pos[5], 0.25f,
					(con->flags & 1) ? 0.6f : 0, 0.6f, c);
		
		dd->end();
	}
	else
	{
		const dtPolyDetail* pd = &tile->detailMeshes[ip];

		dd->begin(DU_DRAW_TRIS);
		for (int i = 0; i < pd->triCount; ++i)
		{
			const unsigned char* t = &tile->detailTris[(pd->triBase+i)*4];
			for (int j = 0; j < 3; ++j)
			{
				if (t[j] < poly->vertCount)
					dd->vertex(&tile->verts[poly->verts[t[j]]*3], c);
				else
					dd->vertex(&tile->detailVerts[(pd->vertBase+t[j]-poly->vertCount)*3], c);
			}
		}
		dd->end();
	}
	
	dd->depthMask(true);

}

static void debugDrawTileCachePortals(struct duDebugDraw* dd, const dtTileCacheLayer& layer, const float cs, const float ch)
{
	const int w = (int)layer.header->width;
	const int h = (int)layer.header->height;
	const float* bmin = layer.header->bmin;

	// Portals
	unsigned int pcol = duRGBA(255,255,255,255);
	
	const int segs[4*4] = {0,0,0,1, 0,1,1,1, 1,1,1,0, 1,0,0,0};
	
	// Layer portals
	dd->begin(DU_DRAW_LINES, 2.0f);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			const int idx = x+y*w;
			const int lh = (int)layer.heights[idx];
			if (lh == 0xff) continue;
			
			for (int dir = 0; dir < 4; ++dir)
			{
				if (layer.cons[idx] & (1<<(dir+4)))
				{
					const int* seg = &segs[dir*4];
					const float ax = bmin[0] + (x+seg[0])*cs;
					const float ay = bmin[1] + (lh+2)*ch;
					const float az = bmin[2] + (y+seg[1])*cs;
					const float bx = bmin[0] + (x+seg[2])*cs;
					const float by = bmin[1] + (lh+2)*ch;
					const float bz = bmin[2] + (y+seg[3])*cs;
					dd->vertex(ax, ay, az, pcol);
					dd->vertex(bx, by, bz, pcol);
				}
			}
		}
	}
	dd->end();
}

void duDebugDrawTileCacheLayerAreas(struct duDebugDraw* dd, const dtTileCacheLayer& layer, const float cs, const float ch)
{
	const int w = (int)layer.header->width;
	const int h = (int)layer.header->height;
	const float* bmin = layer.header->bmin;
	const float* bmax = layer.header->bmax;
	const int idx = layer.header->tlayer;
	
	unsigned int color = duIntToCol(idx+1, 255);
	
	// Layer bounds
	float lbmin[3], lbmax[3];
	lbmin[0] = bmin[0] + layer.header->minx*cs;
	lbmin[1] = bmin[1];
	lbmin[2] = bmin[2] + layer.header->miny*cs;
	lbmax[0] = bmin[0] + (layer.header->maxx+1)*cs;
	lbmax[1] = bmax[1];
	lbmax[2] = bmin[2] + (layer.header->maxy+1)*cs;
	duDebugDrawBoxWire(dd, lbmin[0],lbmin[1],lbmin[2], lbmax[0],lbmax[1],lbmax[2], duTransCol(color,128), 2.0f);
	
	// Layer height
	dd->begin(DU_DRAW_QUADS);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			const int lidx = x+y*w;
			const int lh = (int)layer.heights[lidx];
			if (lh == 0xff) continue;
			const unsigned char area = layer.areas[lidx];
			
			unsigned int col;
			if (area == 63)
				col = duLerpCol(color, duRGBA(0,192,255,64), 32);
			else if (area == 0)
				col = duLerpCol(color, duRGBA(0,0,0,64), 32);
			else
				col = duLerpCol(color, duIntToCol(area, 255), 32);
			
			const float fx = bmin[0] + x*cs;
			const float fy = bmin[1] + (lh+1)*ch;
			const float fz = bmin[2] + y*cs;
			
			dd->vertex(fx, fy, fz, col);
			dd->vertex(fx, fy, fz+cs, col);
			dd->vertex(fx+cs, fy, fz+cs, col);
			dd->vertex(fx+cs, fy, fz, col);
		}
	}
	dd->end();
	
	debugDrawTileCachePortals(dd, layer, cs, ch);
}

void duDebugDrawTileCacheLayerRegions(struct duDebugDraw* dd, const dtTileCacheLayer& layer, const float cs, const float ch)
{
	const int w = (int)layer.header->width;
	const int h = (int)layer.header->height;
	const float* bmin = layer.header->bmin;
	const float* bmax = layer.header->bmax;
	const int idx = layer.header->tlayer;
	
	unsigned int color = duIntToCol(idx+1, 255);
	
	// Layer bounds
	float lbmin[3], lbmax[3];
	lbmin[0] = bmin[0] + layer.header->minx*cs;
	lbmin[1] = bmin[1];
	lbmin[2] = bmin[2] + layer.header->miny*cs;
	lbmax[0] = bmin[0] + (layer.header->maxx+1)*cs;
	lbmax[1] = bmax[1];
	lbmax[2] = bmin[2] + (layer.header->maxy+1)*cs;
	duDebugDrawBoxWire(dd, lbmin[0],lbmin[1],lbmin[2], lbmax[0],lbmax[1],lbmax[2], duTransCol(color,128), 2.0f);
	
	// Layer height
	dd->begin(DU_DRAW_QUADS);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			const int lidx = x+y*w;
			const int lh = (int)layer.heights[lidx];
			if (lh == 0xff) continue;
			const unsigned char reg = layer.regs[lidx];
			
			unsigned int col = duLerpCol(color, duIntToCol(reg, 255), 192);
			
			const float fx = bmin[0] + x*cs;
			const float fy = bmin[1] + (lh+1)*ch;
			const float fz = bmin[2] + y*cs;
			
			dd->vertex(fx, fy, fz, col);
			dd->vertex(fx, fy, fz+cs, col);
			dd->vertex(fx+cs, fy, fz+cs, col);
			dd->vertex(fx+cs, fy, fz, col);
		}
	}
	dd->end();
	
	debugDrawTileCachePortals(dd, layer, cs, ch);
}




/*struct dtTileCacheContour
{
	int nverts;
	unsigned char* verts;
	unsigned char reg;
	unsigned char area;
};

struct dtTileCacheContourSet
{
	int nconts;
	dtTileCacheContour* conts;
};*/

void duDebugDrawTileCacheContours(duDebugDraw* dd, const struct dtTileCacheContourSet& lcset,
								  const float* orig, const float cs, const float ch)
{
	if (!dd) return;
	
	const unsigned char a = 255;// (unsigned char)(alpha*255.0f);
	
	const int offs[2*4] = {-1,0, 0,1, 1,0, 0,-1};
	
	dd->begin(DU_DRAW_LINES, 2.0f);
	
	for (int i = 0; i < lcset.nconts; ++i)
	{
		const dtTileCacheContour& c = lcset.conts[i];
		unsigned int color = 0;
		
		color = duIntToCol(i, a);
		
		for (int j = 0; j < c.nverts; ++j)
		{
			const int k = (j+1) % c.nverts;
			const unsigned char* va = &c.verts[j*4];
			const unsigned char* vb = &c.verts[k*4];
			const float ax = orig[0] + va[0]*cs;
			const float ay = orig[1] + (va[1]+1+(i&1))*ch;
			const float az = orig[2] + va[2]*cs;
			const float bx = orig[0] + vb[0]*cs;
			const float by = orig[1] + (vb[1]+1+(i&1))*ch;
			const float bz = orig[2] + vb[2]*cs;
			unsigned int col = color;
			if ((va[3] & 0xf) != 0xf)
			{
				// Portal segment
				col = duRGBA(255,255,255,128);
				int d = va[3] & 0xf;
				
				const float cx = (ax+bx)*0.5f;
				const float cy = (ay+by)*0.5f;
				const float cz = (az+bz)*0.5f;
				
				const float dx = cx + offs[d*2+0]*2*cs;
				const float dy = cy;
				const float dz = cz + offs[d*2+1]*2*cs;
				
				dd->vertex(cx,cy,cz,duRGBA(255,0,0,255));
				dd->vertex(dx,dy,dz,duRGBA(255,0,0,255));
			}
			
			duAppendArrow(dd, ax,ay,az, bx,by,bz, 0.0f, cs*0.5f, col);
		}
	}
	dd->end();
	
	dd->begin(DU_DRAW_POINTS, 4.0f);	
	
	for (int i = 0; i < lcset.nconts; ++i)
	{
		const dtTileCacheContour& c = lcset.conts[i];
		unsigned int color = 0;
		
		for (int j = 0; j < c.nverts; ++j)
		{
			const unsigned char* va = &c.verts[j*4];
			
			color = duDarkenCol(duIntToCol(i, a));
			if (va[3] & 0x80)
			{
				// Border vertex
				color = duRGBA(255,0,0,255);
			}
			
			float fx = orig[0] + va[0]*cs;
			float fy = orig[1] + (va[1]+1+(i&1))*ch;
			float fz = orig[2] + va[2]*cs;
			dd->vertex(fx,fy,fz, color);
		}
	}
	dd->end();
}

void duDebugDrawTileCachePolyMesh(duDebugDraw* dd, const struct dtTileCachePolyMesh& lmesh,
								  const float* orig, const float cs, const float ch)
{
	if (!dd) return;
	
	const int nvp = lmesh.nvp;
	
	const int offs[2*4] = {-1,0, 0,1, 1,0, 0,-1};
	
	dd->begin(DU_DRAW_TRIS);
	
	for (int i = 0; i < lmesh.npolys; ++i)
	{
		const unsigned short* p = &lmesh.polys[i*nvp*2];
		
		unsigned int color;
		if (lmesh.areas[i] == DT_TILECACHE_WALKABLE_AREA)
			color = duRGBA(0,192,255,64);
		else if (lmesh.areas[i] == DT_TILECACHE_NULL_AREA)
			color = duRGBA(0,0,0,64);
		else
			color = duIntToCol(lmesh.areas[i], 255);
		
		unsigned short vi[3];
		for (int j = 2; j < nvp; ++j)
		{
			if (p[j] == DT_TILECACHE_NULL_IDX) break;
			vi[0] = p[0];
			vi[1] = p[j-1];
			vi[2] = p[j];
			for (int k = 0; k < 3; ++k)
			{
				const unsigned short* v = &lmesh.verts[vi[k]*3];
				const float x = orig[0] + v[0]*cs;
				const float y = orig[1] + (v[1]+1)*ch;
				const float z = orig[2] + v[2]*cs;
				dd->vertex(x,y,z, color);
			}
		}
	}
	dd->end();
	
	// Draw neighbours edges
	const unsigned int coln = duRGBA(0,48,64,32);
	dd->begin(DU_DRAW_LINES, 1.5f);
	for (int i = 0; i < lmesh.npolys; ++i)
	{
		const unsigned short* p = &lmesh.polys[i*nvp*2];
		for (int j = 0; j < nvp; ++j)
		{
			if (p[j] == DT_TILECACHE_NULL_IDX) break;
			if (p[nvp+j] & 0x8000) continue;
			const int nj = (j+1 >= nvp || p[j+1] == DT_TILECACHE_NULL_IDX) ? 0 : j+1; 
			int vi[2] = {p[j], p[nj]};
			
			for (int k = 0; k < 2; ++k)
			{
				const unsigned short* v = &lmesh.verts[vi[k]*3];
				const float x = orig[0] + v[0]*cs;
				const float y = orig[1] + (v[1]+1)*ch + 0.1f;
				const float z = orig[2] + v[2]*cs;
				dd->vertex(x, y, z, coln);
			}
		}
	}
	dd->end();
	
	// Draw boundary edges
	const unsigned int colb = duRGBA(0,48,64,220);
	dd->begin(DU_DRAW_LINES, 2.5f);
	for (int i = 0; i < lmesh.npolys; ++i)
	{
		const unsigned short* p = &lmesh.polys[i*nvp*2];
		for (int j = 0; j < nvp; ++j)
		{
			if (p[j] == DT_TILECACHE_NULL_IDX) break;
			if ((p[nvp+j] & 0x8000) == 0) continue;
			const int nj = (j+1 >= nvp || p[j+1] == DT_TILECACHE_NULL_IDX) ? 0 : j+1; 
			int vi[2] = {p[j], p[nj]};
			
			unsigned int col = colb;
			if ((p[nvp+j] & 0xf) != 0xf)
			{
				const unsigned short* va = &lmesh.verts[vi[0]*3];
				const unsigned short* vb = &lmesh.verts[vi[1]*3];
				
				const float ax = orig[0] + va[0]*cs;
				const float ay = orig[1] + (va[1]+1+(i&1))*ch;
				const float az = orig[2] + va[2]*cs;
				const float bx = orig[0] + vb[0]*cs;
				const float by = orig[1] + (vb[1]+1+(i&1))*ch;
				const float bz = orig[2] + vb[2]*cs;
				
				const float cx = (ax+bx)*0.5f;
				const float cy = (ay+by)*0.5f;
				const float cz = (az+bz)*0.5f;
				
				int d = p[nvp+j] & 0xf;
				
				const float dx = cx + offs[d*2+0]*2*cs;
				const float dy = cy;
				const float dz = cz + offs[d*2+1]*2*cs;
				
				dd->vertex(cx,cy,cz,duRGBA(255,0,0,255));
				dd->vertex(dx,dy,dz,duRGBA(255,0,0,255));
				
				col = duRGBA(255,255,255,128);
			}
			
			for (int k = 0; k < 2; ++k)
			{
				const unsigned short* v = &lmesh.verts[vi[k]*3];
				const float x = orig[0] + v[0]*cs;
				const float y = orig[1] + (v[1]+1)*ch + 0.1f;
				const float z = orig[2] + v[2]*cs;
				dd->vertex(x, y, z, col);
			}
		}
	}
	dd->end();
	
	dd->begin(DU_DRAW_POINTS, 3.0f);
	const unsigned int colv = duRGBA(0,0,0,220);
	for (int i = 0; i < lmesh.nverts; ++i)
	{
		const unsigned short* v = &lmesh.verts[i*3];
		const float x = orig[0] + v[0]*cs;
		const float y = orig[1] + (v[1]+1)*ch + 0.1f;
		const float z = orig[2] + v[2]*cs;
		dd->vertex(x,y,z, colv);
	}
	dd->end();
}



