xof 0303txt 0032
//
// DirectX file: F:\CO1301\Ass2Test\media\Arrow.x
//
// Converted by the PolyTrans geometry converter from Okino Computer Graphics, Inc.
// Date/time of export: 01/03/2012 02:26:05
//
// Bounding box of geometry = (-2.49962,-2.29962,-5) to (2.49962,2.69962,5).


template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
  <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
  <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
  <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
  <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimTicksPerSecond {
 <9e415a43-7ba6-4a73-8743-b73d47e88476>
 DWORD AnimTicksPerSecond; 
}

template FloatKeys {
 <10DD46A9-775B-11cf-8F52-0040333594A3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <F406B180-7B3B-11cf-8F52-0040333594A3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10DD46A8-775B-11cf-8F52-0040333594A3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

template AnimationOptions {
 <E2BF56C0-840F-11cf-8F52-0040333594A3>
 DWORD openclosed;
 DWORD positionquality;
}

template Animation {
 <3D82AB4F-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimationSet {
 <3D82AB50-62DA-11cf-AB39-0020AF71E433>
 [Animation]
}

template XSkinMeshHeader {
 <3CF169CE-FF7C-44ab-93C0-F78F62D172E2>
 WORD nMaxSkinWeightsPerVertex; 
 WORD nMaxSkinWeightsPerFace; 
 WORD nBones; 
}

template SkinWeights {
 <6F0D123B-BAD2-4167-A0D0-80224F25FABB>
 STRING transformNodeName;
 DWORD nWeights; 
 array DWORD vertexIndices[nWeights]; 
 array float weights[nWeights]; 
 Matrix4x4 matrixOffset; 
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF; 
 DWORD nDWords; 
 array DWORD data[nDWords]; 
}

Header {
	1; // Major version
	0; // Minor version
	1; // Flags
}

AnimTicksPerSecond { 3600; }

Material xof_default {
	0.400000;0.400000;0.400000;1.000000;;
	32.000000;
	0.700000;0.700000;0.700000;;
	0.000000;0.000000;0.000000;;
}

Material Material {
	1.0;1.0;1.0;1.000000;;
	0.000000;
	0.000000;0.000000;0.000000;;
	0.000000;0.000000;0.000000;;
	TextureFilename {
		"lava_rock.jpg";
	}
}

// Top-most frame encompassing the 'World'
Frame Frame_World {
	FrameTransformMatrix {
		1.000000, 0.0, 0.0, 0.0, 
		0.0, 1.000000, 0.0, 0.0, 
		0.0, 0.0, -1.000000, 0.0, 
		0.0, 0.0, 0.0, 1.000000;;
	}

Frame Frame_output {
	FrameTransformMatrix {
		1.000000, 0.0, 0.0, 0.0, 
		0.0, 1.000000, 0.0, 0.0, 
		0.0, 0.0, 1.000000, 0.0, 
		0.0, 0.0, 0.0, 1.000000;;
	}

Frame Frame_single_mesh_object__Material {
	FrameTransformMatrix {
		1.000000, 0.0, 0.0, 0.0, 
		0.0, 1.000000, 0.0, 0.0, 
		0.0, 0.0, -1.000000, 0.0, 
		0.0, 0.0, 0.0, 1.000000;;
	}

// Original object name = "single_mesh_object__Material"
Mesh single_mesh_object__Material {
	128;		// 128 vertices
	-2.499619;0.243631;-0.500000;,
	-2.499619;0.243631;-0.500000;,
	-2.390762;-0.530929;-0.500000;,
	-2.390762;-0.530929;-0.500000;,
	-2.363798;1.013921;-0.500000;,
	-2.363798;1.013921;-0.500000;,
	-2.363798;1.013921;-0.500000;,
	-2.047880;-1.233941;-0.500000;,
	-2.047880;-1.233941;-0.500000;,
	-1.996590;1.704538;-0.500000;,
	-1.996590;1.704538;-0.500000;,
	-1.504538;-1.796589;-0.500000;,
	-1.504538;-1.796589;-0.500000;,
	-1.433942;2.247881;-0.500000;,
	-1.433942;2.247881;-0.500000;,
	-1.250000;0.200000;0.000000;,
	-1.250000;0.200000;0.000000;,
	-1.250000;0.200000;-5.000000;,
	-1.250000;0.200000;-5.000000;,
	-1.188821;0.586271;0.000000;,
	-1.188821;0.586271;0.000000;,
	-1.188821;0.586271;0.000000;,
	-1.188821;0.586271;0.000000;,
	-1.188821;0.586271;-5.000000;,
	-1.188821;0.586271;-5.000000;,
	-1.188821;0.586271;-5.000000;,
	-1.188821;0.586271;-5.000000;,
	-1.188821;-0.186271;0.000000;,
	-1.188821;-0.186271;0.000000;,
	-1.188821;-0.186271;-5.000000;,
	-1.188821;-0.186271;-5.000000;,
	-1.011272;0.934732;0.000000;,
	-1.011272;0.934732;0.000000;,
	-1.011272;0.934732;-5.000000;,
	-1.011272;0.934732;-5.000000;,
	-1.011271;-0.534732;0.000000;,
	-1.011271;-0.534732;0.000000;,
	-1.011271;-0.534732;-5.000000;,
	-1.011271;-0.534732;-5.000000;,
	-0.813920;-2.163797;-0.500000;,
	-0.813920;-2.163797;-0.500000;,
	-0.734732;1.211272;0.000000;,
	-0.734732;1.211272;0.000000;,
	-0.734732;1.211272;-5.000000;,
	-0.734732;1.211272;-5.000000;,
	-0.734732;-0.811271;0.000000;,
	-0.734732;-0.811271;0.000000;,
	-0.734732;-0.811271;-5.000000;,
	-0.734732;-0.811271;-5.000000;,
	-0.730930;2.590763;-0.500000;,
	-0.730930;2.590763;-0.500000;,
	-0.386271;1.388821;0.000000;,
	-0.386271;1.388821;0.000000;,
	-0.386271;1.388821;-5.000000;,
	-0.386271;1.388821;-5.000000;,
	-0.386271;-0.988821;0.000000;,
	-0.386271;-0.988821;0.000000;,
	-0.386271;-0.988821;-5.000000;,
	-0.386271;-0.988821;-5.000000;,
	-0.043631;-2.299619;-0.500000;,
	-0.043631;-2.299619;-0.500000;,
	0.000000;-1.050000;-5.000000;,
	0.000000;-1.050000;-5.000000;,
	0.000000;-1.050000;0.000000;,
	0.000000;-1.050000;0.000000;,
	0.000000;1.450001;-5.000000;,
	0.000000;1.450001;-5.000000;,
	0.000000;1.450001;0.000000;,
	0.000000;1.450001;0.000000;,
	0.000000;0.200000;-5.000000;,
	0.000000;0.200000;0.000000;,
	0.000000;0.200000;5.000000;,
	0.043631;2.699620;-0.500000;,
	0.043631;2.699620;-0.500000;,
	0.386271;-0.988821;0.000000;,
	0.386271;-0.988821;0.000000;,
	0.386271;-0.988821;-5.000000;,
	0.386271;-0.988821;-5.000000;,
	0.386271;1.388821;0.000000;,
	0.386271;1.388821;0.000000;,
	0.386271;1.388821;-5.000000;,
	0.386271;1.388821;-5.000000;,
	0.730929;-2.190762;-0.500000;,
	0.730929;-2.190762;-0.500000;,
	0.734732;-0.811271;0.000000;,
	0.734732;-0.811271;0.000000;,
	0.734732;-0.811271;-5.000000;,
	0.734732;-0.811271;-5.000000;,
	0.734732;1.211272;0.000000;,
	0.734732;1.211272;0.000000;,
	0.734732;1.211272;-5.000000;,
	0.734732;1.211272;-5.000000;,
	0.813921;2.563797;-0.500000;,
	0.813921;2.563797;-0.500000;,
	1.011271;-0.534732;0.000000;,
	1.011271;-0.534732;0.000000;,
	1.011271;-0.534732;-5.000000;,
	1.011271;-0.534732;-5.000000;,
	1.011272;0.934732;0.000000;,
	1.011272;0.934732;0.000000;,
	1.011272;0.934732;-5.000000;,
	1.011272;0.934732;-5.000000;,
	1.188821;-0.186271;0.000000;,
	1.188821;-0.186271;0.000000;,
	1.188821;-0.186271;-5.000000;,
	1.188821;-0.186271;-5.000000;,
	1.188821;0.586271;0.000000;,
	1.188821;0.586271;0.000000;,
	1.188821;0.586271;-5.000000;,
	1.188821;0.586271;-5.000000;,
	1.250000;0.200000;0.000000;,
	1.250000;0.200000;0.000000;,
	1.250000;0.200000;-5.000000;,
	1.250000;0.200000;-5.000000;,
	1.433941;-1.847880;-0.500000;,
	1.433941;-1.847880;-0.500000;,
	1.504538;2.196589;-0.500000;,
	1.504538;2.196589;-0.500000;,
	1.996589;-1.304538;-0.500000;,
	1.996589;-1.304538;-0.500000;,
	2.047881;1.633942;-0.500000;,
	2.047881;1.633942;-0.500000;,
	2.363797;-0.613921;-0.500000;,
	2.363797;-0.613921;-0.500000;,
	2.390763;0.930929;-0.500000;,
	2.390763;0.930929;-0.500000;,
	2.499620;0.156369;-0.500000;,
	2.499620;0.156369;-0.500000;;

	118;		// 118 faces
	3;3,1,6;,
	3;8,3,6;,
	3;12,8,6;,
	3;40,12,6;,
	3;60,40,6;,
	3;83,60,6;,
	3;115,83,6;,
	3;119,115,6;,
	3;123,119,6;,
	3;127,123,6;,
	3;125,127,6;,
	3;121,125,6;,
	3;117,121,6;,
	3;93,117,6;,
	3;73,93,6;,
	3;50,73,6;,
	3;14,50,6;,
	3;10,14,6;,
	3;71,9,5;,
	3;71,13,9;,
	3;71,49,13;,
	3;71,72,49;,
	3;71,92,72;,
	3;71,116,92;,
	3;71,120,116;,
	3;71,124,120;,
	3;71,126,124;,
	3;71,122,126;,
	3;71,118,122;,
	3;71,114,118;,
	3;71,82,114;,
	3;71,59,82;,
	3;71,39,59;,
	3;71,11,39;,
	3;71,7,11;,
	3;71,2,7;,
	3;71,0,2;,
	3;71,4,0;,
	3;32,34,26;,
	3;22,32,26;,
	3;42,44,34;,
	3;32,42,34;,
	3;52,54,44;,
	3;42,52,44;,
	3;68,66,54;,
	3;52,68,54;,
	3;79,81,66;,
	3;68,79,66;,
	3;89,91,81;,
	3;79,89,81;,
	3;99,101,91;,
	3;89,99,91;,
	3;107,109,101;,
	3;99,107,101;,
	3;111,113,109;,
	3;107,111,109;,
	3;103,105,113;,
	3;111,103,113;,
	3;95,97,105;,
	3;103,95,105;,
	3;85,87,97;,
	3;95,85,97;,
	3;75,77,87;,
	3;85,75,87;,
	3;64,62,77;,
	3;75,64,77;,
	3;56,58,62;,
	3;64,56,62;,
	3;46,48,58;,
	3;56,46,58;,
	3;36,38,48;,
	3;46,36,48;,
	3;28,30,38;,
	3;36,28,38;,
	3;16,18,30;,
	3;28,16,30;,
	3;21,25,18;,
	3;16,21,18;,
	3;69,24,33;,
	3;69,33,43;,
	3;69,43,53;,
	3;69,53,65;,
	3;69,65,80;,
	3;69,80,90;,
	3;69,90,100;,
	3;69,100,108;,
	3;69,108,112;,
	3;69,112,104;,
	3;69,104,96;,
	3;69,96,86;,
	3;69,86,76;,
	3;69,76,61;,
	3;69,61,57;,
	3;69,57,47;,
	3;69,47,37;,
	3;69,37,29;,
	3;69,29,17;,
	3;69,17,23;,
	3;70,31,20;,
	3;70,41,31;,
	3;70,51,41;,
	3;70,67,51;,
	3;70,78,67;,
	3;70,88,78;,
	3;70,98,88;,
	3;70,106,98;,
	3;70,110,106;,
	3;70,102,110;,
	3;70,94,102;,
	3;70,84,94;,
	3;70,74,84;,
	3;70,63,74;,
	3;70,55,63;,
	3;70,45,55;,
	3;70,35,45;,
	3;70,27,35;,
	3;70,15,27;,
	3;70,19,15;;

	MeshMaterialList {
		1;1;0;;
		{Material}
	}

	MeshNormals {
		42; // 42 normals
		-1.000000;0.000000;0.000000;,
		-0.951057;0.309016;0.000000;,
		-0.951057;-0.309017;0.000000;,
		-0.910228;0.015888;0.413803;,
		-0.870588;-0.266165;0.413803;,
		-0.860769;0.296386;0.413803;,
		-0.809017;-0.587785;0.000000;,
		-0.809017;0.587785;0.000000;,
		-0.745729;-0.522165;0.413803;,
		-0.727051;0.547872;0.413803;,
		-0.587785;-0.809017;0.000000;,
		-0.587785;0.809017;0.000000;,
		-0.547872;-0.727051;0.413803;,
		-0.522165;0.745728;0.413803;,
		-0.309017;-0.951057;0.000000;,
		-0.309017;0.951057;0.000000;,
		-0.296386;-0.860768;0.413803;,
		-0.266165;0.870588;0.413803;,
		-0.015888;-0.910228;0.413803;,
		0.000000;-1.000000;0.000000;,
		0.000000;0.000000;-1.000000;,
		0.000000;0.000000;1.000000;,
		0.000000;1.000000;0.000000;,
		0.015888;0.910228;0.413803;,
		0.266165;-0.870588;0.413803;,
		0.296386;0.860768;0.413803;,
		0.309017;-0.951057;0.000000;,
		0.309017;0.951056;0.000000;,
		0.522165;-0.745729;0.413803;,
		0.547872;0.727051;0.413803;,
		0.587785;-0.809017;0.000000;,
		0.587785;0.809017;0.000000;,
		0.727051;-0.547872;0.413803;,
		0.745729;0.522165;0.413803;,
		0.809017;-0.587785;0.000000;,
		0.809017;0.587785;0.000000;,
		0.860768;-0.296386;0.413803;,
		0.870588;0.266165;0.413803;,
		0.910228;-0.015888;0.413803;,
		0.951057;-0.309017;0.000000;,
		0.951057;0.309017;0.000000;,
		1.000000;0.000000;0.000000;;

		118;		// 118 faces
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;21,9,5;,
		3;21,13,9;,
		3;21,17,13;,
		3;21,23,17;,
		3;21,25,23;,
		3;21,29,25;,
		3;21,33,29;,
		3;21,37,33;,
		3;21,38,37;,
		3;21,36,38;,
		3;21,32,36;,
		3;21,28,32;,
		3;21,24,28;,
		3;21,18,24;,
		3;21,16,18;,
		3;21,12,16;,
		3;21,8,12;,
		3;21,4,8;,
		3;21,3,4;,
		3;21,5,3;,
		3;7,7,1;,
		3;1,7,1;,
		3;11,11,7;,
		3;7,11,7;,
		3;15,15,11;,
		3;11,15,11;,
		3;22,22,15;,
		3;15,22,15;,
		3;27,27,22;,
		3;22,27,22;,
		3;31,31,27;,
		3;27,31,27;,
		3;35,35,31;,
		3;31,35,31;,
		3;40,40,35;,
		3;35,40,35;,
		3;41,41,40;,
		3;40,41,40;,
		3;39,39,41;,
		3;41,39,41;,
		3;34,34,39;,
		3;39,34,39;,
		3;30,30,34;,
		3;34,30,34;,
		3;26,26,30;,
		3;30,26,30;,
		3;19,19,26;,
		3;26,19,26;,
		3;14,14,19;,
		3;19,14,19;,
		3;10,10,14;,
		3;14,10,14;,
		3;6,6,10;,
		3;10,6,10;,
		3;2,2,6;,
		3;6,2,6;,
		3;0,0,2;,
		3;2,0,2;,
		3;1,1,0;,
		3;0,1,0;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;20,20,20;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;,
		3;21,21,21;;
	}  // End of Normals

	MeshTextureCoords {
		128; // 128 texture coords
		0.950000;1.000000;,
		1.000000;1.500000;,
		0.900000;1.000000;,
		0.975528;1.345492;,
		1.000000;1.000000;,
		0.000000;1.000000;,
		0.975528;1.654509;,
		0.850000;1.000000;,
		0.904509;1.206107;,
		0.050000;1.000000;,
		0.904509;1.793893;,
		0.800000;1.000000;,
		0.793893;1.095491;,
		0.100000;1.000000;,
		0.793893;1.904509;,
		0.950000;0.204225;,
		0.950000;0.204225;,
		0.950000;0.840845;,
		0.950000;0.840845;,
		1.000000;0.204225;,
		0.000000;0.204225;,
		1.000000;0.204225;,
		0.000000;0.204225;,
		1.000000;0.840845;,
		0.000000;0.840845;,
		1.000000;0.840845;,
		0.000000;0.840845;,
		0.900000;0.204225;,
		0.900000;0.204225;,
		0.900000;0.840845;,
		0.900000;0.840845;,
		0.050000;0.204225;,
		0.050000;0.204225;,
		0.050000;0.840845;,
		0.050000;0.840845;,
		0.850000;0.204225;,
		0.850000;0.204225;,
		0.850000;0.840845;,
		0.850000;0.840845;,
		0.750000;1.000000;,
		0.654509;1.024472;,
		0.100000;0.204225;,
		0.100000;0.204225;,
		0.100000;0.840845;,
		0.100000;0.840845;,
		0.800000;0.204225;,
		0.800000;0.204225;,
		0.800000;0.840845;,
		0.800000;0.840845;,
		0.150000;1.000000;,
		0.654509;1.975528;,
		0.150000;0.204225;,
		0.150000;0.204225;,
		0.150000;0.840845;,
		0.150000;0.840845;,
		0.750000;0.204225;,
		0.750000;0.204225;,
		0.750000;0.840845;,
		0.750000;0.840845;,
		0.700000;1.000000;,
		0.500000;1.000000;,
		0.700000;0.840845;,
		0.700000;0.840845;,
		0.700000;0.204225;,
		0.700000;0.204225;,
		0.200000;0.840845;,
		0.200000;0.840845;,
		0.200000;0.204225;,
		0.200000;0.204225;,
		0.500000;1.000000;,
		0.500000;0.045070;,
		0.500000;0.000000;,
		0.200000;1.000000;,
		0.500000;2.000000;,
		0.650000;0.204225;,
		0.650000;0.204225;,
		0.650000;0.840845;,
		0.650000;0.840845;,
		0.250000;0.204225;,
		0.250000;0.204225;,
		0.250000;0.840845;,
		0.250000;0.840845;,
		0.650000;1.000000;,
		0.345491;1.024472;,
		0.600000;0.204225;,
		0.600000;0.204225;,
		0.600000;0.840845;,
		0.600000;0.840845;,
		0.300000;0.204225;,
		0.300000;0.204225;,
		0.300000;0.840845;,
		0.300000;0.840845;,
		0.250000;1.000000;,
		0.345491;1.975528;,
		0.550000;0.204225;,
		0.550000;0.204225;,
		0.550000;0.840845;,
		0.550000;0.840845;,
		0.350000;0.204225;,
		0.350000;0.204225;,
		0.350000;0.840845;,
		0.350000;0.840845;,
		0.500000;0.204225;,
		0.500000;0.204225;,
		0.500000;0.840845;,
		0.500000;0.840845;,
		0.400000;0.204225;,
		0.400000;0.204225;,
		0.400000;0.840845;,
		0.400000;0.840845;,
		0.450000;0.204225;,
		0.450000;0.204225;,
		0.450000;0.840845;,
		0.450000;0.840845;,
		0.600000;1.000000;,
		0.206107;1.095491;,
		0.300000;1.000000;,
		0.206107;1.904509;,
		0.550000;1.000000;,
		0.095491;1.206107;,
		0.350000;1.000000;,
		0.095491;1.793893;,
		0.500000;1.000000;,
		0.024472;1.345491;,
		0.400000;1.000000;,
		0.024472;1.654509;,
		0.450000;1.000000;,
		0.000000;1.500000;;
	}  // End of texture coords
} // End of Mesh
} // End of frame for 'single_mesh_object__Material'
} // End empty node 'output' frame
} // End of "World" frame
