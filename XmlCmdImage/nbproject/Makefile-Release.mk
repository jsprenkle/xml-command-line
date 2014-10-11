#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++-4.7
CXX=g++-4.7
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/23690359/XmlCmd.Image.o \
	${OBJECTDIR}/_ext/23690359/XmlCmd.ImageReader.o \
	${OBJECTDIR}/_ext/23690359/XmlCmd.ImageWriter.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxmlcmdimage.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxmlcmdimage.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxmlcmdimage.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxmlcmdimage.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxmlcmdimage.a

${OBJECTDIR}/_ext/23690359/XmlCmd.Image.o: ../XmlCmdImage/XmlCmd.Image.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/23690359
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -I. -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/23690359/XmlCmd.Image.o ../XmlCmdImage/XmlCmd.Image.cpp

${OBJECTDIR}/_ext/23690359/XmlCmd.ImageReader.o: ../XmlCmdImage/XmlCmd.ImageReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/23690359
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -I. -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/23690359/XmlCmd.ImageReader.o ../XmlCmdImage/XmlCmd.ImageReader.cpp

${OBJECTDIR}/_ext/23690359/XmlCmd.ImageWriter.o: ../XmlCmdImage/XmlCmd.ImageWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/23690359
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -I. -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/23690359/XmlCmd.ImageWriter.o ../XmlCmdImage/XmlCmd.ImageWriter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxmlcmdimage.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
