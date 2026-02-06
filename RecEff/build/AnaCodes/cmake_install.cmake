# Install script for directory: /work/clas12/marianak/git/Clas12_Analysis/RecEff/AnaCodes

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/work/clas12/marianak/builds/RecEff")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer.exe"
         RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/Reducer.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE EXECUTABLE FILES "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/Reducer.exe")
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer.exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer.exe"
         OLD_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/lib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib:"
         NEW_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/CMakeFiles/Reducer.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer_TBTracks2.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer_TBTracks2.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer_TBTracks2.exe"
         RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/Reducer_TBTracks2.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE EXECUTABLE FILES "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/Reducer_TBTracks2.exe")
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer_TBTracks2.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer_TBTracks2.exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer_TBTracks2.exe"
         OLD_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/lib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib:"
         NEW_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Reducer_TBTracks2.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/CMakeFiles/Reducer_TBTracks2.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis.exe"
         RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/Analysis.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE EXECUTABLE FILES "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/Analysis.exe")
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis.exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis.exe"
         OLD_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/lib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib:"
         NEW_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/CMakeFiles/Analysis.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis_beforereducing.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis_beforereducing.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis_beforereducing.exe"
         RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/Analysis_beforereducing.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE EXECUTABLE FILES "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/Analysis_beforereducing.exe")
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis_beforereducing.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis_beforereducing.exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis_beforereducing.exe"
         OLD_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/lib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib:"
         NEW_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Analysis_beforereducing.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/CMakeFiles/Analysis_beforereducing.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plots.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plots.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plots.exe"
         RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/Eff_plots.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE EXECUTABLE FILES "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/Eff_plots.exe")
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plots.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plots.exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plots.exe"
         OLD_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/lib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib:"
         NEW_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plots.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/CMakeFiles/Eff_plots.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum.exe"
         RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE EXECUTABLE FILES "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/Eff_plot_lum.exe")
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum.exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum.exe"
         OLD_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/lib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib:"
         NEW_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/CMakeFiles/Eff_plot_lum.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum_aiTracking.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum_aiTracking.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum_aiTracking.exe"
         RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum_aiTracking.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE EXECUTABLE FILES "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/Eff_plot_lum_aiTracking.exe")
  if(EXISTS "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum_aiTracking.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum_aiTracking.exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum_aiTracking.exe"
         OLD_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/lib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib:"
         NEW_RPATH "/work/clas12/marianak/git/Clas12_Analysis/RecEff/RecEffLib:/u/scigroup/cvmfs/hallb/clas12/sw/almalinux9-gcc11/local/root/6.36.04/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/work/clas12/marianak/builds/RecEff/bin/Eff_plot_lum_aiTracking.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/work/clas12/marianak/git/Clas12_Analysis/RecEff/build/AnaCodes/CMakeFiles/Eff_plot_lum_aiTracking.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE DIRECTORY FILES "")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/work/clas12/marianak/builds/RecEff/bin/Compare_Rec_Red.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/work/clas12/marianak/builds/RecEff/bin" TYPE FILE FILES "/work/clas12/marianak/git/Clas12_Analysis/RecEff/AnaCodes/Compare_Rec_Red.py")
endif()

