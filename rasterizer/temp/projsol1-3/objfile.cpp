////////////////////////////////////////////////////////////////////////////////
// objfile.cpp
///////////////////////////////////// 

#include "objfile.h"

/////////////////////////////////////////////////////////////////////////////
// Name:           get_indices 
// Arguments:      parametirs for vertex texture and normal indices
// Returns:        none
// Side Effects:   none
/////////////////////////////////////////////////////////////////////////////
void get_indices(char *word, int *vindex, int *tindex, int *nindex)
{
	char *null = " ";
	char *ptr;
	char *tp;
	char *np;

	/* by default, the texture and normal pointers are set to the null string */
	tp = null;
	np = null;

	/* replace slashes with null characters and cause tp and np to point */
	/* to character immediately following the first or second slash */

	for (ptr = word; *ptr != '\0'; ptr++) {
		if (*ptr == '/') {
			if (tp == null)
				tp = ptr + 1;
			else
				np = ptr + 1;

			*ptr = '\0';
		}
	}

	*vindex = atoi (word);
	*tindex = atoi (tp);
	*nindex = atoi (np);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           ObjFile constructor
// Arguments:      The filename for the Wavefront OBJ file, and an initial 
// 				   transform matrix (useful for scaling)
// Returns:        none
// Side Effects:   fills the Model class with vertex and normal data from the
//                 model file on disk.
/////////////////////////////////////////////////////////////////////////////

ObjFile::ObjFile(char* fileName,Matrix &M)
{

	FILE * fp = fopen(fileName,"r");
	int &nv=numVertices, &nn=numNormals, &nf=numTriangles,nt=0;
	char line[81];
	while ( fgets( line, 80, fp ) != NULL ) {
		if (line[0] == 'v') {
			if (line[1] == 'n')
				nn++;
			else if (line[1] == 't')
				nt++;
			else
				nv++;
		} else if (line[0] == 'f') {
			nf++;
		}
	}
	fseek(fp, 0, 0);

	pNormals = new Vector3[nn>nf?nn:nf];
	pVertices = new Point3[nv];

//	if (nt) { // got texture coordinates
//		pTexCoords = new VectorR2[nt];
//		pTexCoordIndices = new TupleI3[nf];
//	}
//	pNormalIndices = new TupleI3[nf]; // always make normals
//	pVertexIndices = new TupleI3[nf]; // always have vertices
	
	pTris = new Triangle[nf];

	int nTriangles = 0;
	int nvertices = 0;
	int nnormals = 0;
	int ntextures = 0;

	while ( fgets( line, 80, fp ) != NULL ) {
		if (line[0] == 'v') {
			if (line[1] == 'n') {
				float x, y, z;
				sscanf( &line[2], "%f %f %f\n", &x, &y, &z);
				Vector3 n(x, y, z);
				pNormals[nnormals] = M*n;
				pNormals[nnormals].Normalize();
				nnormals++;
			} else if (line[1] == 't') {
				//float x, y;
				//sscanf( &line[2], "%f %f\n", &x, &y);
				//pTexCoords[ntextures].x = x;
				//pTexCoords[ntextures].y = y;
				//ntextures++;
			} else {
				float x, y, z;
				sscanf( &line[1], "%f %f %f\n", &x, &y, &z);
				Point3 v(x, y, z);
				pVertices[nvertices] = M*v;
				nvertices++;
			}
		} else if (line[0] == 'f') {
			char s1[32], s2[32], s3[32];
			int v, t, n;
			sscanf( &line[1], "%s %s %s\n", s1, s2, s3);

			get_indices(s1, &v, &t, &n);
			pTris[nTriangles].VertexIndices[0] = v-1;
			if (n)
				pTris[nTriangles].NormalIndices[0] = n-1;
			//if (t)
			//	pTexCoordIndices[nTriangles].x = t-1;
			get_indices(s2, &v, &t, &n);
			pTris[nTriangles].VertexIndices[1] = v-1;
			if (n)
				pTris[nTriangles].NormalIndices[1] = n-1;
			//if (t)
			//	pTexCoordIndices[nTriangles].y = t-1;
			
			get_indices(s3, &v, &t, &n);
			pTris[nTriangles].VertexIndices[2] = v-1;
			if (n)
				pTris[nTriangles].NormalIndices[2] = n-1;
			//if (t)
			//	pTexCoordIndices[nTriangles].z = t-1;

			if (!n) 
			{ // if no normal was supplied
				Vector3 e1 = pVertices[pTris[nTriangles].VertexIndices[1]] - pVertices[pTris[nTriangles].VertexIndices[0]];
				Vector3 e2 = pVertices[pTris[nTriangles].VertexIndices[2]] - pVertices[pTris[nTriangles].VertexIndices[0]];
				pNormals[nn].Cross(e1,e2);
				pNormals[nn].Normalize();
				pTris[nTriangles].SetNormals(nn,nn,nn);
				nn++;
			}

			nTriangles++;
		} //  else ignore line
	}
	fprintf(stderr,"done reading in OBJ file..\n");
	fprintf(stderr,"obj file read in: numVertices: %d, numNormals: %d, numTriangles: %d\n",numVertices,numNormals,numTriangles);
}

