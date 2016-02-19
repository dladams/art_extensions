# art_extensions/test/utilities/CMakeLists.txt

cet_test(test_huffman SOURCES test_huffman.cxx
  LIBRARIES
    lardata_RawData
)

cet_test(test_Compress SOURCES test_Compress.cxx
  LIBRARIES
    lardata_RawData
)
