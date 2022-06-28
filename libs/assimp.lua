project "Assimp"
  kind "StaticLib"
  language "C++"
  cppdialect "C++11"
  staticruntime "on"

  targetdir "../bin/%{cfg.buildcfg}"
  objdir "../obj/%{cfg.buildcfg}"

  defines 
  {
              -- "SWIG",
        "ASSIMP_BUILD_NO_OWN_ZLIB",

        "ASSIMP_BUILD_NO_X_IMPORTER",
        "ASSIMP_BUILD_NO_3DS_IMPORTER",
        "ASSIMP_BUILD_NO_MD3_IMPORTER",
        "ASSIMP_BUILD_NO_MDL_IMPORTER",
        "ASSIMP_BUILD_NO_MD2_IMPORTER",
        "ASSIMP_BUILD_NO_PLY_IMPORTER",
        "ASSIMP_BUILD_NO_ASE_IMPORTER",
        -- "ASSIMP_BUILD_NO_OBJ_IMPORTER",
        "ASSIMP_BUILD_NO_AMF_IMPORTER",
        "ASSIMP_BUILD_NO_HMP_IMPORTER",
        "ASSIMP_BUILD_NO_SMD_IMPORTER",
        "ASSIMP_BUILD_NO_MDC_IMPORTER",
        "ASSIMP_BUILD_NO_MD5_IMPORTER",
        "ASSIMP_BUILD_NO_STL_IMPORTER",
        "ASSIMP_BUILD_NO_LWO_IMPORTER",
        "ASSIMP_BUILD_NO_DXF_IMPORTER",
        "ASSIMP_BUILD_NO_NFF_IMPORTER",
        "ASSIMP_BUILD_NO_RAW_IMPORTER",
        "ASSIMP_BUILD_NO_OFF_IMPORTER",
        "ASSIMP_BUILD_NO_AC_IMPORTER",
        "ASSIMP_BUILD_NO_BVH_IMPORTER",
        "ASSIMP_BUILD_NO_IRRMESH_IMPORTER",
        "ASSIMP_BUILD_NO_IRR_IMPORTER",
        "ASSIMP_BUILD_NO_Q3D_IMPORTER",
        "ASSIMP_BUILD_NO_B3D_IMPORTER",
        "ASSIMP_BUILD_NO_COLLADA_IMPORTER",
        "ASSIMP_BUILD_NO_TERRAGEN_IMPORTER",
        "ASSIMP_BUILD_NO_CSM_IMPORTER",
        "ASSIMP_BUILD_NO_3D_IMPORTER",
        "ASSIMP_BUILD_NO_LWS_IMPORTER",
        "ASSIMP_BUILD_NO_OGRE_IMPORTER",
        "ASSIMP_BUILD_NO_OPENGEX_IMPORTER",
        "ASSIMP_BUILD_NO_MS3D_IMPORTER",
        "ASSIMP_BUILD_NO_COB_IMPORTER",
        "ASSIMP_BUILD_NO_BLEND_IMPORTER",
        "ASSIMP_BUILD_NO_Q3BSP_IMPORTER",
        "ASSIMP_BUILD_NO_NDO_IMPORTER",
        "ASSIMP_BUILD_NO_IFC_IMPORTER",
        "ASSIMP_BUILD_NO_XGL_IMPORTER",
        "ASSIMP_BUILD_NO_FBX_IMPORTER",
        "ASSIMP_BUILD_NO_ASSBIN_IMPORTER",
        "ASSIMP_BUILD_NO_GLTF_IMPORTER",
        "ASSIMP_BUILD_NO_C4D_IMPORTER",
        "ASSIMP_BUILD_NO_3MF_IMPORTER",
        "ASSIMP_BUILD_NO_X3D_IMPORTER",
        "ASSIMP_BUILD_NO_MMD_IMPORTER",
        "ASSIMP_BUILD_NO_M3D_IMPORTER",
        "ASSIMP_BUILD_NO_IQM_IMPORTER",
            
        "ASSIMP_BUILD_NO_STEP_EXPORTER",
        "ASSIMP_BUILD_NO_SIB_IMPORTER",

        -- "ASSIMP_BUILD_NO_MAKELEFTHANDED_PROCESS",
        "ASSIMP_BUILD_NO_FLIPUVS_PROCESS",
        -- "ASSIMP_BUILD_NO_FLIPWINDINGORDER_PROCESS",
        -- "ASSIMP_BUILD_NO_CALCTANGENTS_PROCESS",
        "ASSIMP_BUILD_NO_JOINVERTICES_PROCESS",
        -- "ASSIMP_BUILD_NO_TRIANGULATE_PROCESS",
        "ASSIMP_BUILD_NO_GENFACENORMALS_PROCESS",
        -- "ASSIMP_BUILD_NO_GENVERTEXNORMALS_PROCESS",
        "ASSIMP_BUILD_NO_REMOVEVC_PROCESS",
        "ASSIMP_BUILD_NO_SPLITLARGEMESHES_PROCESS",
        "ASSIMP_BUILD_NO_PRETRANSFORMVERTICES_PROCESS",
        "ASSIMP_BUILD_NO_LIMITBONEWEIGHTS_PROCESS",
        -- "ASSIMP_BUILD_NO_VALIDATEDS_PROCESS",
        "ASSIMP_BUILD_NO_IMPROVECACHELOCALITY_PROCESS",
        "ASSIMP_BUILD_NO_FIXINFACINGNORMALS_PROCESS",
        "ASSIMP_BUILD_NO_REMOVE_REDUNDANTMATERIALS_PROCESS",
        "ASSIMP_BUILD_NO_FINDINVALIDDATA_PROCESS",
        "ASSIMP_BUILD_NO_FINDDEGENERATES_PROCESS",
        "ASSIMP_BUILD_NO_SORTBYPTYPE_PROCESS",
        "ASSIMP_BUILD_NO_GENUVCOORDS_PROCESS",
        "ASSIMP_BUILD_NO_TRANSFORMTEXCOORDS_PROCESS",
        "ASSIMP_BUILD_NO_FINDINSTANCES_PROCESS",
        "ASSIMP_BUILD_NO_OPTIMIZEMESHES_PROCESS",
        "ASSIMP_BUILD_NO_OPTIMIZEGRAPH_PROCESS",
        "ASSIMP_BUILD_NO_SPLITBYBONECOUNT_PROCESS",
        "ASSIMP_BUILD_NO_DEBONE_PROCESS",
        "ASSIMP_BUILD_NO_EMBEDTEXTURES_PROCESS",
        "ASSIMP_BUILD_NO_GLOBALSCALE_PROCESS",
  }

  files {
      "include/**",
      "assimp/code/AssetLib/Obj/ObjFileImporter.cpp",
      "assimp/code/AssetLib/Obj/ObjFileMtlImporter.cpp",
      "assimp/code/AssetLib/Obj/ObjFileParser.cpp",
      "assimp/code/Common/Assimp.cpp",
      "assimp/code/Common/AssertHandler.cpp",
      "assimp/code/Common/BaseImporter.cpp",
      "assimp/code/Common/CreateAnimMesh.cpp",
      "assimp/code/Common/BaseProcess.cpp",
      "assimp/code/Common/DefaultIOStream.cpp",
      "assimp/code/Common/DefaultIOSystem.cpp",
      "assimp/code/Common/Exceptional.cpp",
      "assimp/code/Common/IOSystem.cpp",
      "assimp/code/Common/DefaultLogger.cpp",
      "assimp/code/Common/Importer.cpp",
      "assimp/code/Common/ImporterRegistry.cpp",
      "assimp/code/Common/Material.cpp",
      "assimp/code/Common/PostStepRegistry.cpp",
      "assimp/code/Common/scene.cpp",
      "assimp/code/Common/ScenePreprocessor.cpp",
      "assimp/code/Common/SGSpatialSort.cpp",
      "assimp/code/Common/SkeletonMeshBuilder.cpp",
      "assimp/code/Common/SpatialSort.cpp",
      "assimp/code/Common/Version.cpp",
      "assimp/code/Common/VertexTriangleAdjacency.cpp",
      "assimp/code/Material/MaterialSystem.cpp",
      "assimp/code/PostProcessing/ArmaturePopulate.cpp",
      "assimp/code/PostProcessing/EmbedTexturesProcess.cpp",
      "assimp/code/PostProcessing/ConvertToLHProcess.cpp",
      "assimp/code/PostProcessing/GenVertexNormalsProcess.cpp",
      "assimp/code/PostProcessing/GenBoundingBoxesProcess.cpp",
      "assimp/code/PostProcessing/ProcessHelper.cpp",
      "assimp/code/PostProcessing/ScaleProcess.cpp",
      "assimp/code/PostProcessing/TriangulateProcess.cpp",
      "assimp/code/PostProcessing/ValidateDataStructure.cpp",
      "assimp/code/PostProcessing/MakeVerboseFormat.cpp",
      "assimp/code/PostProcessing/CalcTangentsProcess.cpp",
      "assimp/contrib/irrXML/*",
  }

  includedirs{
    "assimp/"
  }

  sysincludedirs {
      "assimp/include",
      "assimp/code",
      "assimp/contrib/irrXML",
      "assimp/contrib/pugixml/src",
      "assimp/contrib/zlib",
      "assimp/contrib/rapidjson/include",
      "assimp/contrib"
  }


filter {"system:macosx", "action:xcode4"}
  systemversion "latest"
  staticruntime "On"

  defines
  {
      "_ASSIMP_COCOA"
  }

filter "system:linux"
  pic "On"

  systemversion "latest"
  staticruntime "On"

  defines
  {
      "_ASSIMP_X11"
  }

filter "system:windows"
  systemversion "latest"
  staticruntime "On"

  defines 
  { 
      "_ASSIMP_WIN32",
      "_CRT_SECURE_NO_WARNINGS"
  }

   filter  "configurations:Debug"
       runtime "Debug"
       symbols "on"

   filter  "configurations:Release"
       runtime "Release"
       optimize "on"