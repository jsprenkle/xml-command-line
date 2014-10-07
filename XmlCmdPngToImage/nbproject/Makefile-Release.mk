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
	${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.App.o \
	${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.Config.Reader.o \
	${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.Config.Settings.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=../lodepng/dist/Release/GNU-Linux-x86/liblodepng.a ../XmlCmd/dist/Release/GNU-Linux-x86/libxmlcmd.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdPngToImage

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdPngToImage: ../lodepng/dist/Release/GNU-Linux-x86/liblodepng.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdPngToImage: ../XmlCmd/dist/Release/GNU-Linux-x86/libxmlcmd.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdPngToImage: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdPngToImage ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.App.o: ../XmlCmdPngToImage/XmlCmdPngToImage.App.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41244727
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../rapidxml-1.13 -I../XmlCmd -I../lodepng -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.App.o ../XmlCmdPngToImage/XmlCmdPngToImage.App.cpp

${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.Config.Reader.o: ../XmlCmdPngToImage/XmlCmdPngToImage.Config.Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41244727
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../rapidxml-1.13 -I../XmlCmd -I../lodepng -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.Config.Reader.o ../XmlCmdPngToImage/XmlCmdPngToImage.Config.Reader.cpp

${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.Config.Settings.o: ../XmlCmdPngToImage/XmlCmdPngToImage.Config.Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41244727
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../rapidxml-1.13 -I../XmlCmd -I../lodepng -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/41244727/XmlCmdPngToImage.Config.Settings.o ../XmlCmdPngToImage/XmlCmdPngToImage.Config.Settings.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../rapidxml-1.13 -I../XmlCmd -I../lodepng -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../lodepng && ${MAKE}  -f Makefile CONF=Release
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdPngToImage

# Subprojects
.clean-subprojects:
	cd ../lodepng && ${MAKE}  -f Makefile CONF=Release clean
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
