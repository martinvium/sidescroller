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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/TutorialApplication.o \
	${OBJECTDIR}/BaseApplication.o


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
LDLIBSOPTIONS=-L/C/OgreSDK/lib/debug -L/C/OgreSDK/boost_1_44/lib -lOgreMain_d.dll -lOIS_d.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk /C/OgreSDK/bin/Debug/ogretutorial.exe

/C/OgreSDK/bin/Debug/ogretutorial.exe: ${OBJECTFILES}
	${MKDIR} -p /C/OgreSDK/bin/Debug
	${LINK.cc} -o C:/OgreSDK/bin/Debug/ogretutorial ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/TutorialApplication.o: TutorialApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_WINDOWS -D_DEBUG -I/C/OgreSDK/include -I/C/OgreSDK/include/OGRE -I/C/OgreSDK/include/OIS -I/C/OgreSDK/Samples/Common/include -I/C/OgreSDK/boost_1_44 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TutorialApplication.o TutorialApplication.cpp

${OBJECTDIR}/BaseApplication.o: BaseApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DWIN32 -D_WINDOWS -D_DEBUG -I/C/OgreSDK/include -I/C/OgreSDK/include/OGRE -I/C/OgreSDK/include/OIS -I/C/OgreSDK/Samples/Common/include -I/C/OgreSDK/boost_1_44 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BaseApplication.o BaseApplication.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} /C/OgreSDK/bin/Debug/ogretutorial.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
