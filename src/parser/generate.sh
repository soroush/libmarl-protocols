#!/bin/bash
xsdcxx cxx-parser --std c++11 --generate-xml-schema --guard-prefix LIBMARL_ --hxx-suffix .hpp --ixx-suffix .ipp --cxx-suffix .cpp --fwd-suffix -fwd.hpp ../../docs/environment.xsd
xsdcxx cxx-parser --std c++11 --guard-prefix LIBMARL --hxx-suffix .hpp --ixx-suffix .ipp --cxx-suffix .cpp --fwd-suffix -fwd.hpp --file-per-type --xml-parser xerces --generate-validation --type-map environment.map ../../docs/environment.xsd
