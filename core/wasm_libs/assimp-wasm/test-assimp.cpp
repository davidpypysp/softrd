#include <stdio.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <string>
bool doImport( const std::string& pFile)
{
  printf("now importing file: %s \n", pFile.c_str());
  Assimp::Importer importer;
  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll 
  // propably to request more postprocessing than we do in this example.
  const aiScene* scene = importer.ReadFile( pFile, 
					    aiProcess_CalcTangentSpace       | 
					    aiProcess_Triangulate            |
					    aiProcess_JoinIdenticalVertices  |
					    aiProcess_SortByPType);
  
  // If the import failed, report it
  if( !scene)
    {
      printf("FAILED importing file: %s \n", pFile.c_str());
      return false;
    }
  // Now we can access the file's contents. 
  printf("SUCCESS importing file: %s \n", pFile.c_str());
  // DoTheSceneProcessing( scene);
  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}
int main (){
  doImport("data/suzanne.blend");
  printf("\nsup ?\n");

}


