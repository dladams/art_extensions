# art_extensions/test/event/CMakeLists.txt

cet_test(test_EventID SOURCES test_EventID.cxx
  LIBRARIES
    ${ART_FRAMEWORK_CORE}
)

cet_test(test_Event SOURCES test_Event.cxx
  LIBRARIES
    ${ART_FRAMEWORK_CORE}
)
