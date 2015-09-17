# art_extensions/test/AXService/CMakeLists.txt

cet_test(test_ArtServiceHelper SOURCES test_ArtServiceHelper.cxx
  LIBRARIES
    AXService
    art_Framework_Services_Optional_TFileService_service
    art_Framework_Services_Optional_RandomNumberGenerator_service
)

install_source()
