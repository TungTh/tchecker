# This file is a part of the TChecker project.
#
# See files AUTHORS and LICENSE for copyright details.

option(TCK_ENABLE_COVREACH_TESTS "enable tests related to covreach" ON)

if(NOT TCK_ENABLE_COVREACH_TESTS)
    message(STATUS "Covreach tests are disabled.")
    return()
endif()

set(PARSE_LABELS_SH "${CMAKE_CURRENT_SOURCE_DIR}/parse-labels.sh")

# Elements of INPUTS are colon-separated lists. The first element of each
# list is a test-case script located in ${EXAMPLES_DIR}; the tail of the list
# contains arguments passed to the generator script.
set(INPUTS
    ad94.sh:
    corsso.sh:2:2:10:1:2
    critical-region.sh:3:10
    critical-region-async.sh:2:10
    csmacd.sh:3
    dining-philosophers.sh:3:3:10:0
    fischer.sh:3:10
    fischer-async.sh:3:10
    parallel.sh:5
    parallel-b.sh:3
    parallel-c.sh:3

    #    train_gate.sh:3 # problem with async_zg:extraLU+l
    )

set(ACCEPT_TEST_REGEX "")
set(REJECT_TEST_REGEX "^.*inclusion.*NOextra.*$")

# dot format is disabled because generated graphs use addresses of states as
# node identifiers
set(COVREACH_OUTPUT_FORMATS
    raw
    #dot
    )

set(COVREACH_SEARCH_ORDERS
    dfs
    bfs
    )

set(COVREACH_ZONE_GRAPHS
    zg
    async_zg
    )

set(COVREACH_SEMANTICS
    elapsed
    non-elapsed
    )

set(COVREACH_ZG_EXTRAPOLATIONS
    NOextra
    extraMg
    extraMl
    extraM+g
    extraM+l
    extraLUg
    extraLUl
    extraLU+g
    extraLU+l
    )

set(COVREACH_ASYNC_ZG_EXTRAPOLATIONS
    extraLU+l
    )

set(COVREACH_ZG_COVERS
    inclusion
    aLUg
    aLUl
    aMg
    aMl
    )
set(COVREACH_ASYNC_ZG_COVERS
    inclusion
    )

file(RELATIVE_PATH here ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "Generating '${here}' tests. This may take a long time.")
tck_register_testcases("covreach-" CHECK_TESTCASES_ savelist COVREACH_INPUT_FILES ${INPUTS})

set(nb_tests 0)
foreach (inputfile ${COVREACH_INPUT_FILES})
    get_filename_component(testname ${inputfile} NAME_WE)

#    set(regex "^# *labels *= *\([a-zA-Z0-9_,]*\) *\$")
#    file(STRINGS "${inputfile}" labels REGEX "${regex}" LIMIT_COUNT 1)
#    if (labels)
#        string(REGEX REPLACE ${regex} "\\1" labels "${labels}")
#        set(labels "-l ${labels}")
#    endif ()

    foreach (zonegraph ${COVREACH_ZONE_GRAPHS})
        if (zonegraph STREQUAL "zg")
            set(EXTRAPOLATIONS ${COVREACH_ZG_EXTRAPOLATIONS})
            set(COVERS ${COVREACH_ZG_COVERS})
        else ()
            set(EXTRAPOLATIONS ${COVREACH_ASYNC_ZG_EXTRAPOLATIONS})
            set(COVERS ${COVREACH_ASYNC_ZG_COVERS})
        endif ()
        foreach (cover ${COVERS})
            foreach (extra ${EXTRAPOLATIONS})
                foreach (sem ${COVREACH_SEMANTICS})
                    set(model "${zonegraph}:${sem}:${extra}")
                    string(REPLACE ":" "_" testname_model "${model}")

                    foreach (outformat ${COVREACH_OUTPUT_FORMATS})
                        foreach (so ${COVREACH_SEARCH_ORDERS})
                            set(TEST_NAME "${testname}_${cover}_${testname_model}_${so}_${outformat}")
                            tck_filter_testcase(accepted ${TEST_NAME} ACCEPT_TEST_REGEX REJECT_TEST_REGEX)
                            if(NOT accepted)
                                continue()
                            endif()

                            tck_add_test (${TEST_NAME} ${TEST_NAME} savelist)

                            set_tests_properties(${TEST_NAME}
                                                 PROPERTIES FIXTURES_REQUIRED "BUILD_TCHECKER;CHECK_TESTCASES_${testname}")

                            tck_add_test_envvar(testenv TEST "${PARSE_LABELS_SH}")
                            tck_add_test_envvar(testenv TEST_ARGS "${TCHECKER} covreach -c ${cover} -f ${outformat} -m ${model} -s ${so} -S ${labels} ${inputfile}")
                            tck_set_test_env(${TEST_NAME} testenv)
                            unset(testenv)
                            math(EXPR nb_tests "${nb_tests}+1")
                        endforeach ()
                    endforeach ()
                endforeach ()
            endforeach ()
        endforeach ()
    endforeach ()
endforeach ()

message(STATUS "${nb_tests} generated tests in ${here}.")

tck_add_savelist(save-covreach ${savelist})