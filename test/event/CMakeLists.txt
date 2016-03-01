# art_extensions/test/event/CMakeLists.txt

cet_test(test_EventID SOURCES test_EventID.cxx
  LIBRARIES
    ${ART_FRAMEWORK_CORE}
    ${ART_UTILITIES}
    cetlib
)

cet_test(test_Timestamp SOURCES test_Timestamp.cxx
  LIBRARIES
    ${ART_PERSISTENCY_PROVENANCE}
)

cet_test(test_Event SOURCES test_Event.cxx
  LIBRARIES
    ${ART_FRAMEWORK_PRINCIPAL}
    ${ART_FRAMEWORK_CORE}
    ${ART_PERSISTENCY_PROVENANCE}
    ${ART_UTILITIES}
    fhiclcpp
    cetlib
)
