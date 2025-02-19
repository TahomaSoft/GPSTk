set( SD ${GPSTK_TEST_DATA_DIR} )
set( TD ${GPSTK_TEST_OUTPUT_DIR} )

###############################################################################
# TEST PRSolve
###############################################################################

# test with minimum required inputs - RINEX obs, SP3 Ephemeris, Solution Descriptor
set( ARGS1 --obs\ ${GPSTK_TEST_DATA_DIR}/arlm200b.15o\ --eph\ ${GPSTK_TEST_DATA_DIR}/test_input_sp3_nav_2015_200.sp3\ --sol\ GPS:12:WC\ --log\ ${TD}/PRSolve_Required.out )
add_test(NAME PRSolve_Required
    COMMAND ${CMAKE_COMMAND}
    -DTEST_PROG=$<TARGET_FILE:PRSolve>
    -DDIFF_PROG=$<TARGET_FILE:df_diff>
    -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
    -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
    -DTESTBASE=PRSolve_Required
    -DTESTNAME=PRSolve_Required
    -DARGS=${ARGS1}
    -DDIFF_ARGS=-l52\ -z1
    -DOWNOUTPUT=1
    -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# test with minimum required inputs, RINEX output - RINEX obs, SP3 Ephemeris, Solution Descriptor, adequate ephemerides
set( ARGS2 --obs\ ${GPSTK_TEST_DATA_DIR}/arlm200b.15o\ --eph\ ${GPSTK_TEST_DATA_DIR}/test_input_sp3_nav_2015_200.sp3\ --sol\ GPS:12:WC\ --out\ ${TD}/PRSolve_Rinexout.out\ --log\ ${TD}/PRSolve_Rinexout.log)
add_test(NAME PRSolve_Rinexout
    COMMAND ${CMAKE_COMMAND}
    -DTEST_PROG=$<TARGET_FILE:PRSolve>
    -DDIFF_PROG=$<TARGET_FILE:df_diff>
    -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
    -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
    -DTESTBASE=PRSolve_Rinexout
    -DTESTNAME=PRSolve_Rinexout
    -DARGS=${ARGS2}
    -DDIFF_ARGS=-l2
    -DOWNOUTPUT=1
    -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test that the output of PRSolve_Rinexout is a valid Rinex Obs file.
add_test(NAME PRSolve_ValidOutput
    COMMAND ${CMAKE_COMMAND}
    -DTEST_PROG=$<TARGET_FILE:rowcheck>
    -DARGS=${TD}/PRSolve_Rinexout.out
    -DTESTBASE=PRSolve_ValidOutput
    -DTESTNAME=PRSolve_ValidOutput
    -DTARGETDIR=${TD}
    -DNODIFF=1
    -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)
set_tests_properties(PRSolve_ValidOutput PROPERTIES DEPENDS PRSolve_Rinexout)


###############################################################################
# TEST poscvt
###############################################################################

# check that -h option is valid
add_test(NAME poscvt_CmdOpt_1
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testhelp.cmake)

# no options should result in failure
add_test(NAME poscvt_CmdOpt_2
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testfailexp.cmake)

# Test ECEF conversion
add_test(NAME poscvt_ECEF
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DTESTBASE=poscvt_ECEF
         -DTESTNAME=poscvt_ECEF
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test Geodetic conversion
add_test(NAME poscvt_Geodetic
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DTESTBASE=poscvt_Geodetic
         -DTESTNAME=poscvt_Geodetic
         -DSPARG1=--geodetic=30.38366382\ 262.27458654\ 217.6452
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test Geocentric conversion
add_test(NAME poscvt_Geocentric
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DTESTBASE=poscvt_Geocentric
         -DTESTNAME=poscvt_Geocentric
         -DSPARG1=--geocentric=30.21602743\ 262.27458654\ 6372918.0945
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test Spherical conversion
add_test(NAME poscvt_Spherical
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DTESTBASE=poscvt_Spherical
         -DTESTNAME=poscvt_Spherical
         -DSPARG1=--spherical=59.78397257\ 262.27458654\ 6372918.0945
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test formatted output
add_test(NAME poscvt_Format_1
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -DTESTBASE=poscvt_Format_1
         -DTESTNAME=poscvt_Format_1
         -DSPARG2=--output-format=%X\ %Y\ %Z
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test formatted output
add_test(NAME poscvt_Format_2
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -DTESTBASE=poscvt_Format_2
         -DTESTNAME=poscvt_Format_2
         -DSPARG2=--output-format=%x\ %y\ %z
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test formatted output
add_test(NAME poscvt_Format_3
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -DTESTBASE=poscvt_Format_3
         -DTESTNAME=poscvt_Format_3
         -DSPARG2=--output-format=%a\ %l\ %r
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test formatted output
add_test(NAME poscvt_Format_4
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -DTESTBASE=poscvt_Format_4
         -DTESTNAME=poscvt_Format_4
         -DSPARG2=--output-format=%A\ %L\ %h
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test formatted output
add_test(NAME poscvt_Format_5
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -DTESTBASE=poscvt_Format_5
         -DTESTNAME=poscvt_Format_5
         -DSPARG2=--output-format=%a\ %w\ %R
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test formatted output
add_test(NAME poscvt_Format_6
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -DTESTBASE=poscvt_Format_6
         -DTESTNAME=poscvt_Format_6
         -DSPARG2=--output-format=%A\ %W\ %H
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test formatted output
add_test(NAME poscvt_Format_7
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -DTESTBASE=poscvt_Format_7
         -DTESTNAME=poscvt_Format_7
         -DSPARG2=--output-format=%t\ %p\ %r
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)

# Test formatted output
add_test(NAME poscvt_Format_8
         COMMAND ${CMAKE_COMMAND}
         -DTEST_PROG=$<TARGET_FILE:poscvt>
         -DSOURCEDIR=${GPSTK_TEST_DATA_DIR}
         -DTARGETDIR=${GPSTK_TEST_OUTPUT_DIR}
         -DSPARG1=--ecef=-740289.9180\ -5457071.7340\ 3207245.5420
         -DTESTBASE=poscvt_Format_8
         -DTESTNAME=poscvt_Format_8
         -DSPARG2=--output-format=%T\ %P\ %R
         -P ${CMAKE_CURRENT_SOURCE_DIR}/../testsuccexp.cmake)
