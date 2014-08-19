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
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lsXml.Config.Reader.o \
	${OBJECTDIR}/lsXml.Config.Settings.o \
	${OBJECTDIR}/lsXml.FileSystem.o \
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
LDLIBSOPTIONS=../XmlCmd/dist/Release/MinGW-Windows/libxmlcmd.a -lWs2_32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lsXmlCmd.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lsXmlCmd.exe: ../XmlCmd/dist/Release/MinGW-Windows/libxmlcmd.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lsXmlCmd.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lsXmlCmd ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/lsXml.Config.Reader.o: lsXml.Config.Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/lsXml.Config.Reader.o lsXml.Config.Reader.cpp

${OBJECTDIR}/lsXml.Config.Settings.o: lsXml.Config.Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/lsXml.Config.Settings.o lsXml.Config.Settings.cpp

${OBJECTDIR}/lsXml.FileSystem.o: lsXml.FileSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/lsXml.FileSystem.o lsXml.FileSystem.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lsXmlCmd.exe

# Subprojects
.clean-subprojects:
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
