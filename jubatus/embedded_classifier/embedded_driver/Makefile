all:
	g++ -shared -fPIC -o libjubatus_embedded_classifier.so $(LDFLAGS) classifier.cpp classifier_c.cpp  $(shell pkg-config --cflags --libs pficommon) $(shell pkg-config --cflags --libs jubatus) -ljubastorage -ljubaconverter -ljubatus_driver -ljubatus_classifier
	ln -s libjubatus_embedded_classifier.so libjubatus_embedded_classifier.dylib
