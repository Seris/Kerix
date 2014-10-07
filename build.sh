#! /bin/bash

${PRINTF} "\e[0;33mBuilding kerix-${VERSION}.${SUBVERSION}.${PATCHLEVEL} ";
${PRINTF} "(${NAME})\e[m\n";

# Getting files lists for compilation
${PRINTF} "\e[0;35mGetting folders/files to create compilation tree...\e[m";

  cd ${root}/${srctree};
  SRC_DIRECTORIES=$(${FIND} ./ -type d -name "*");
  SRC_FILES=$(${FIND} ./ -type f -name "*");
  cd ${root}/${archtree};
  ARCH_DIRECTORIES=$(${FIND} ./ -type d -name "*");
  ARCH_FILES=$(${FIND} ./ -type f -name "*");
  cd ${root};

${PRINTF} "\e[0;32m Success\e[m\n\n"


# Creating tree for compilation
${PRINTF} "\e[0;35mCreating virtualtree for compilation...\e[m";

  for dir in $ARCH_DIRECTORIES $SRC_DIRECTORIES; do
    ${MKDIR} -p $virtualtree/$dir || { 
      ${PRINTF} "\e[0;31m Failed\e[m\n" ; ${EXIT} 1; 
    };
  done;

  for file in $SRC_FILES; do
    ${LN} -sf ${root}/${srctree}/$file ${virtualtree}/$file  || { 
      ${PRINTF} "\e[0;31m Failed\e[m\n" ; ${EXIT} 1; 
    };
  done;

  for file in $ARCH_FILES; do
    ${LN} -sf ${root}/${archtree}/$file ${virtualtree}/$file  || { 
      ${PRINTF} "\e[0;31m Failed\e[m\n" ; ${EXIT} 1; 
    };
  done;

${PRINTF} "\e[0;32m Success\e[m\n\n"

cd ${virtualtree}
${PRINTF} "\e[0;35mCompiling Kerix...\e[m\n";

# Build
MAIN_DIRECTORIES=$(${LS} -p | ${GREP} "/" --color=never  | ${SED} 's/\///')
for dir in $MAIN_DIRECTORIES; do
  if [[ -f $dir/Makefile ]]; then
    ${PRINTF} "\e[0;34mBuilding /$dir\e[m\n\e[0;36m"

    ${MAKE} DIR="$dir" all --directory=$dir || { 
      ${PRINTF} "\e[0;31m/$dir : Failed\e[m\n" ; ${EXIT} 1; 
    };

    ${PRINTF} "\e[0;32m/$dir : Success\e[m\n\n"
  else
    ${PRINTF} "\e[0;31m/!\ '/$dir' doesn't have any Makefile /!\ \e[m\n";
  fi;
done;

${PRINTF} "\e[0;32mKernel builded\e[m\n\n"

${PRINTF} "\e[0;35mGetting compiled files/libraries for linking...\e[m";
# Getting all objects/static libraries
  # Searching for the init object
  INIT_OBJ=$(${FIND} boot/ -name ${INIT_OBJ_NAME})
  if [[ -z $INIT_OBJ ]]; then
    ${PRINTF} "\e[0;31m/!\ No ${INIT_OBJ_NAME} found, aborting /!\ \e[m\n";
    exit 1;
  fi;

  # List other object/libraries
  OBJ=$(${FIND} . -name "export-*.o" -not -name "${INIT_OBJ_NAME}")
  LIB=$(${FIND} . -name "export-*.a" -not -name "${INIT_OBJ_NAME}")

  ${PRINTF} "\e[0;32m Success\e[m\n\n\e[0;36m"

# Linking the kernel
echo "${LD} ${LDFLAGS} -T setup.ld ${INIT_OBJ} ${OBJ} ${LIB} -o ${OUTPUT} "
${LD} ${LDFLAGS} -T setup.ld ${OBJ} ${LIB} ${INIT_OBJ} -o ${OUTPUT} || {
  ${PRINTF} "\e[0;31mFailed to link, aborting\e[m\n" ; ${EXIT} 1; 
};

${PRINTF} "\e[0;32mKerix builded !\e[m\n\n\e[0;36m"