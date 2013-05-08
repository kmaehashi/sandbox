all:
	g++ -shared -o libjubatus_embedded_classifier.dylib $(LDFLAGS) classifier.cpp classifier_c.cpp  $(shell pkg-config --cflags --libs pficommon) $(shell pkg-config --cflags --libs jubatus) -ljubastorage -ljubaconverter -ljubatus_driver -ljubatus_classifier
