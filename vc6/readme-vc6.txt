If you are having problems with building under VC6 please make sure you have the latest service pack, ZEngine uses the STL which some of the VC6 service packs fixed. For more help come to the ZEngine forums at Concept of Zero.
http://www.conceptofzero.net/forums/index.php?act=SF&f=15

VC6 has very odd tendencies in Debug mode, if you are trying to run the test programs from VC6 and it simply crashes, you need to make a copy of the /test/bin/data folder and place it at /vc6/data.  This should resolve problems.