# art_extensions/exe/fcl/CMakeLists.txt
#
# David Adams
# November 2015
#
# Instructions to build and install fcldump.

cet_make_exec(fcldump
  SOURCE fcldump.cxx
  LIBRARIES
   fhiclcpp
    cetlib
)

install_source()
