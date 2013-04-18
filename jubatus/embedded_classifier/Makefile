all:
	g++ test.cpp embedded_driver/classifier.cpp -o test $(shell pkg-config --cflags --libs pficommon) $(shell pkg-config --cflags --libs jubatus) -ljubastorage -ljubaconverter -ljubatus_driver -ljubatus_classifier
