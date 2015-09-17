# art_extensions/test/services/CMakeLists.txt

cet_test(test_TFileService SOURCES test_TFileService.cxx
  LIBRARIES
    AXService
    art_Framework_Services_Optional_TFileService_service
)

cet_test(test_Geometry SOURCES test_Geometry.cxx
  LIBRARIES
    AXService
    Geometry
)

cet_test(test_RandomNumberGenerator SOURCES test_RandomNumberGenerator.cxx
  LIBRARIES
    AXService
    art_Framework_Services_Optional_RandomNumberGenerator_service
)

cet_test(test_TimeService SOURCES test_TimeService.cxx
  LIBRARIES
    AXService
    TimeService_service
)

cet_test(test_DetectorProperties SOURCES test_DetectorProperties.cxx
  LIBRARIES
    AXService
    DetectorProperties_service
)

cet_test(test_LArProperties SOURCES test_LArProperties.cxx
  LIBRARIES
    AXService
    LArProperties_service
)

install_source()
