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
	${OBJECTDIR}/XmlCmdToJpg.Config.Reader.o \
	${OBJECTDIR}/XmlCmdToJpg.Config.Settings.o \
	${OBJECTDIR}/XmlCmdToJpg.File.Reader.o \
	${OBJECTDIR}/XmlCmdToJpg.File.Writer.o \
	${OBJECTDIR}/XmlCmdToJpg.ImageReader.o \
	${OBJECTDIR}/XmlCmdToJpg.ImageWriter.o \
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
LDLIBSOPTIONS=../XmlCmd/dist/Linux_Release/GNU-Linux-x86/libxmlcmd.a ../JpgLib/dist/Linux_Release/GNU-Linux-x86/libjpglib.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimagetojpg

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimagetojpg: ../XmlCmd/dist/Linux_Release/GNU-Linux-x86/libxmlcmd.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimagetojpg: ../JpgLib/dist/Linux_Release/GNU-Linux-x86/libjpglib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimagetojpg: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimagetojpg ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/XmlCmdToJpg.Config.Reader.o: XmlCmdToJpg.Config.Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I../rapidxml-1.13 -I../XmlCmd -I../JpgLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdToJpg.Config.Reader.o XmlCmdToJpg.Config.Reader.cpp

${OBJECTDIR}/XmlCmdToJpg.Config.Settings.o: XmlCmdToJpg.Config.Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I../rapidxml-1.13 -I../XmlCmd -I../JpgLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdToJpg.Config.Settings.o XmlCmdToJpg.Config.Settings.cpp

${OBJECTDIR}/XmlCmdToJpg.File.Reader.o: XmlCmdToJpg.File.Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I../rapidxml-1.13 -I../XmlCmd -I../JpgLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdToJpg.File.Reader.o XmlCmdToJpg.File.Reader.cpp

${OBJECTDIR}/XmlCmdToJpg.File.Writer.o: XmlCmdToJpg.File.Writer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I../rapidxml-1.13 -I../XmlCmd -I../JpgLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdToJpg.File.Writer.o XmlCmdToJpg.File.Writer.cpp

${OBJECTDIR}/XmlCmdToJpg.ImageReader.o: XmlCmdToJpg.ImageReader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I../rapidxml-1.13 -I../XmlCmd -I../JpgLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdToJpg.ImageReader.o XmlCmdToJpg.ImageReader.cpp

${OBJECTDIR}/XmlCmdToJpg.ImageWriter.o: XmlCmdToJpg.ImageWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I../rapidxml-1.13 -I../XmlCmd -I../JpgLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdToJpg.ImageWriter.o XmlCmdToJpg.ImageWriter.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I../rapidxml-1.13 -I../XmlCmd -I../JpgLib -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Linux_Release
	cd ../JpgLib && ${MAKE}  -f Makefile CONF=Linux_Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimagetojpg

# Subprojects
.clean-subprojects:
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Linux_Release clean
	cd ../JpgLib && ${MAKE}  -f Makefile CONF=Linux_Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
