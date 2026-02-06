set(INCLUDES
        ${ROOT_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/hipo/hipo4)
include_directories(${INCLUDES})
link_directories(${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_VERBOSE_MAKEFILE ON)

################################  Adding Executables  ##########################################
add_executable(Reducer Reducer.cc)   #create target executable based on Reducer.cc
set_target_properties(Reducer PROPERTIES OUTPUT_NAME "Reducer.exe")   # assign name to executable
target_link_libraries(Reducer Hipo4 ${ROOT_LIBRARIES} )    #Link libraries to executable

add_executable(Reducer_TBTracks2 Reducer_TBTracks2.cc)   #create target executable based on Reducer_TBTracks2.cc
set_target_properties(Reducer_TBTracks2 PROPERTIES OUTPUT_NAME "Reducer_TBTracks2.exe")   # assign name to executable
target_link_libraries(Reducer_TBTracks2 Hipo4 ${ROOT_LIBRARIES} )    #Link libraries to executable

add_executable(Analysis Analysis.cc)   #create target executable based on Analysis.cc
set_target_properties(Analysis PROPERTIES OUTPUT_NAME "Analysis.exe")   # assign name to executable
target_link_libraries(Analysis Hipo4 ${ROOT_LIBRARIES} )    #Link libraries to executable

add_executable(Analysis_beforereducing Analysis_beforereducing.cc)   #create target executable based on Analysis.cc
set_target_properties(Analysis_beforereducing PROPERTIES OUTPUT_NAME "Analysis_beforereducing.exe")   # assign name to executable
target_link_libraries(Analysis_beforereducing Hipo4 ${ROOT_LIBRARIES} )    #Link libraries to executable

add_executable(Eff_plots Eff_plots.cc)   #create target executable based on Analysis.cc
set_target_properties(Eff_plots PROPERTIES OUTPUT_NAME "Eff_plots.exe")   # assign name to executable
target_link_libraries(Eff_plots Hipo4 ${ROOT_LIBRARIES} )    #Link libraries to executable

add_executable(Eff_plot_lum Eff_plot_lum.cc)   #create target executable based on Analysis.cc
set_target_properties(Eff_plot_lum PROPERTIES OUTPUT_NAME "Eff_plot_lum.exe")   # assign name to executable
target_link_libraries(Eff_plot_lum Hipo4 ${ROOT_LIBRARIES} )    #Link libraries to executable

add_executable(Eff_plot_lum_aiTracking Eff_plot_lum_aiTracking.cc)   #create target executable based on Analysis.cc
set_target_properties(Eff_plot_lum_aiTracking PROPERTIES OUTPUT_NAME "Eff_plot_lum_aiTracking.exe")   # assign name to executable
target_link_libraries(Eff_plot_lum_aiTracking Hipo4 ${ROOT_LIBRARIES} )    #Link libraries to executable
#################################################################################################

################################ Installing Executable targets #############################
install( TARGETS Reducer Reducer_TBTracks2 Analysis Analysis_beforereducing Eff_plots Eff_plot_lum Eff_plot_lum_aiTracking
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )

################################ Installing needed directores ##############################
install( DIRECTORY
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES Compare_Rec_Red.py
DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)