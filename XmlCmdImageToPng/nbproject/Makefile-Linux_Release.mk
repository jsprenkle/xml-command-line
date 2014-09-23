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
CND_CONF=Linux_Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/File.Reader.o \
	${OBJECTDIR}/File.Writer.o \
	${OBJECTDIR}/XmlCmdImageToPng.Config.Reader.o \
	${OBJECTDIR}/XmlCmdImageToPng.Config.Settings.o \
	${OBJECTDIR}/XmlCmdImageToPng.Convert.o \
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
LDLIBSOPTIONS=../lodepng/dist/Linux_Release/GNU-Linux-x86/liblodepng.a ../XmlCmd/dist/Linux_Release/GNU-Linux-x86/libxmlcmd.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdImageToPng

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdImageToPng: ../lodepng/dist/Linux_Release/GNU-Linux-x86/liblodepng.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdImageToPng: ../XmlCmd/dist/Linux_Release/GNU-Linux-x86/libxmlcmd.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdImageToPng: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdImageToPng ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/File.Reader.o: File.Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../lodepng -I../rapidxml-1.13 -I../XmlCmd -MMD -MP -MF $@.d -o ${OBJECTDIR}/File.Reader.o File.Reader.cpp

${OBJECTDIR}/File.Writer.o: File.Writer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../lodepng -I../rapidxml-1.13 -I../XmlCmd -MMD -MP -MF $@.d -o ${OBJECTDIR}/File.Writer.o File.Writer.cpp

${OBJECTDIR}/XmlCmdImageToPng.Config.Reader.o: XmlCmdImageToPng.Config.Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../lodepng -I../rapidxml-1.13 -I../XmlCmd -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdImageToPng.Config.Reader.o XmlCmdImageToPng.Config.Reader.cpp

${OBJECTDIR}/XmlCmdImageToPng.Config.Settings.o: XmlCmdImageToPng.Config.Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../lodepng -I../rapidxml-1.13 -I../XmlCmd -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdImageToPng.Config.Settings.o XmlCmdImageToPng.Config.Settings.cpp

${OBJECTDIR}/XmlCmdImageToPng.Convert.o: XmlCmdImageToPng.Convert.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../lodepng -I../rapidxml-1.13 -I../XmlCmd -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdImageToPng.Convert.o XmlCmdImageToPng.Convert.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../lodepng -I../rapidxml-1.13 -I../XmlCmd -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../lodepng && ${MAKE}  -f Makefile CONF=Linux_Release
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Linux_Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlCmdImageToPng

# Subprojects
.clean-subprojects:
	cd ../lodepng && ${MAKE}  -f Makefile CONF=Linux_Release clean
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Linux_Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
