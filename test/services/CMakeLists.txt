# art_extensions/test/services/CMakeLists.txt

cet_test(test_TFileService SOURCES test_TFileService.cxx
  LIBRARIES
    AXService
    art_Framework_Services_Optional_TFileService_service
    ${ART_FRAMEWORK_SERVICES_OPTIONAL}
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_Geometry SOURCES test_Geometry.cxx
  LIBRARIES
    AXService
    Geometry
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_RandomNumberGenerator SOURCES test_RandomNumberGenerator.cxx
  LIBRARIES
    AXService
    art_Framework_Services_Optional_RandomNumberGenerator_service
    ${ART_FRAMEWORK_CORE}
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_TimeService SOURCES test_TimeService.cxx
  LIBRARIES
    AXService
    TimeService_service
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_DetectorProperties SOURCES test_DetectorProperties.cxx
  LIBRARIES
    AXService
    DetectorProperties_service
    ${ART_UTILITIES}
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_LArProperties SOURCES test_LArProperties.cxx
  LIBRARIES
    AXService
    LArProperties_service
)

cet_test(test_SeedService SOURCES test_SeedService.cxx
  LIBRARIES
    AXService
    SeedService_service
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_SignalShapingServiceDUNE35t SOURCES test_SignalShapingServiceDUNE35t.cxx
  LIBRARIES
    AXService
    SignalShapingServiceDUNE35t_service
)

install_source()
