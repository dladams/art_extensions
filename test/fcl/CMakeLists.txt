# art_extensions/test/fcl/CMakeLists.txt

cet_test(fcldump SOURCES fcldump.cxx
  LIBRARIES
    fhiclcpp
    cetlib
)

install_source()
