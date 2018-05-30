#!/bin/bash

xsdcxx cxx-parser --std c++11 --guard-prefix LIBMARL --hxx-suffix .hpp --ixx-suffix .ipp --cxx-suffix .cpp --fwd-suffix -fwd.hpp --xml-parser xerces --generate-validation --type-map environment-map.map --generate-xml-schema ../../docs/mdp.xsd

xsdcxx cxx-parser --std c++11 --guard-prefix LIBMARL --hxx-suffix .hpp --ixx-suffix .ipp --cxx-suffix .cpp --fwd-suffix -fwd.hpp --file-per-type --xml-parser xerces --generate-validation --type-map environment-map.map --extern-xml-schema ./mdp-pskel.hpp ../../docs/mdp.xsd
