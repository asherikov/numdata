FIND_SOURCES=find ./test/ ./include/ -iname "*.h" -or -iname "*.cpp"

install_ubuntu_test_deps: install_deps_common
	${APT_INSTALL} libboost-all-dev

test: clean
	${MAKE} cppcheck
	${MAKE} spell
	${MAKE} unit_tests OPTIONS=test

clean: clean_common

dox: doxclean clean
	cd doc; doxygen

format:
	${FIND_SOURCES} | xargs ${CLANG_FORMAT} -verbose -i

adddeps:
	-git remote remove double-conversion
	git remote add double-conversion https://github.com/google/double-conversion

updatedeps:
	git fetch --all
	git rm --ignore-unmatch -rf google-double-conversion
	git read-tree --prefix=google-double-conversion -u 4f7a25d8ced8c7cf6eee6fd09d6788eaa23c9afe
