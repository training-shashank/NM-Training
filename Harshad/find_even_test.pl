# COPYRIGHT: (C) 2015 - All rights reserved - Network Marvels (I) Pvt. Ltd.,
# Thane (India)
#-------------------------------------------------------------------------------
# File: find_even_test_script.pl
# Author: Harshad
# Date: 14-Jul-2015
#
# Description: Process test data to set parameters for number validation.
#
# The test data is taken as input from a file. It is upto the tester to create
# the test data file. There is no validation on what is in the test data file.
# The control lies with the tester as far as test data file is concerned. It is
# assumed that the tester knows what he is feeding in to the test data file for
# purpose of creating valid invalid test scenarios.
#
# Following tags are supported:
# ------------------------------------------------------------------------------
# NUMBER - offset number
# RANGE - range of even numbers
# OUTPUT - expected output
# ERROR_OUTPUT - The error message expected by program.
#
# CAUTION:
# ------------------------------------------------------------------------------
# Program does not validate the sequence of input in the test data.
# It is upto the tester to build the test case hence the tester has full flex-
# -bility to enter data in the sequence (s)he decides
#-------------------------------------------------------------------------------

#------------------------------Modules------------------------------------------
use strict;                                                                     
use warnings;
#use diagnostics;
#-------------------------------------------------------------------------------

#-----------------------------I/O Files-----------------------------------------
open my $test_data, "+<", "/home/harshad/dump/text-files/find_test.txt" or      
    die "Can't open data file $!";                                             
open my $test_log, "+>>", "/home/harshad/dump/test-scripts/find_test_log.txt" or 
    die "Can't open log file $!";                                              
#-------------------------------------------------------------------------------

#--------------------------Global Declarations----------------------------------
my $number1 = 0;
my $number2 = 0;
my $log_rec_no = 0;
#-------------------------------------------------------------------------------
    
#--------------------------Global Declarations----------------------------------
#sub validate_output (@, @);
#sub update_test_log (@, @, $);
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
 # Sub-routine: validate_output
 # Working: This routine checks whether actual output is equal to the expected
 #          output.
 # Input: Actual & expected output.
#-------------------------------------------------------------------------------

sub validate_output {

    print "In validate\n";
    my $flag = 0;

    my @c_output = @{$_[0]};
    my @words = @{$_[1]};
    my $op_format = $_[2];

    my $arr_size = @c_output;

    foreach my $i (@c_output){
        print "output: $i\n";
    }
    print "Actual output: @c_output\n";
    print "Expected output: @words\n";
    print "Array size: $arr_size\n";
    my $words_size = @words;
    print "Words size: $words_size\n";

    # both array should contain same number of elements
    if ( $arr_size == $words_size ){
        
        print "same length\n";   
        # checking for array elements
        for ( my $i = 0; $i < @words; $i++ ){
            print "c_output[$i]: $c_output[$i]\n";
            print "words[$i]: $words[$i]\n";
            
            # compare string output
            if ( $op_format ){
                if ( $c_output[$i] eq $words[$i] ){
                    $flag = 1;
                    next ;
                }
                else{
                    $flag = 0;
                    last ;
                }
            }

            # compare numeric output
            else{
                if ( $c_output[$i] == $words[$i] ){
                    $flag = 1;
                    next ;
                }
                else{
                    $flag = 0;
                    last ;
                }
            }
        }

        # if all array elements are equal
        if ( $flag == 1 ){
            print "case successful\n\n";
            update_test_log(\@c_output, \@words, "Passed");
        }
        else{
            print "case unsuccessful\n\n";
            update_test_log(\@c_output, \@words, "Failed");
        }
    }
    else{
        print "case unsuccessful\n\n";
        update_test_log(\@c_output, \@words, "Failed");
    }           
}

#-------------------------------------------------------------------------------
 # Sub-routine: update_test_log
 # Working: This routine updates the log for testing.
 # Input: Actual output, expected output and test result.
#-------------------------------------------------------------------------------

sub update_test_log{
    
    print "In update\n";
    
    my @c_output = @{$_[0]};
    my @words = @{$_[1]};
    $log_rec_no++;

    my $result = $_[2];

    print "Writing to log...\n";
    
    # check if file is empty with -s
    # returns the size of file

    if ( !-s $test_log ){
        print $test_log "\tId\t|\tTimestamp\t\t|\tExpected output\t\t|".
                        "\tActual output\t\t|\tTest Result\n";
        print $test_log "----------------------------------------------------".
          "------------------------------------------------------------------".
          "----------------------------------------------------------------\n";
    }

    my $time = localtime();

    # to distinguish between different runs
    if ( $log_rec_no == 1 ){
        print $test_log "=====================================================".
          "===================================================================".
          "=================================================================\n";
    }     

    print $test_log "\t$log_rec_no\t|\t$time\t|\t@words\t|".
                    "\t@c_output\t|\t$result\t\n";
        
    print $test_log "----------------------------------------------------".
          "------------------------------------------------------------------".
          "----------------------------------------------------------------\n";
}

foreach my $line ( <$test_data> ){

    # store line read from the test cases file
    my @words = split ' ', $line;
    
    # ignore comments in script file
    if ( $words[0] eq '#' ){
        next ;
    }

    # scan for the number
    elsif ( $words[0] eq "NUMBER" ){
        $number1 = $words[1];
        next;
    }

    # scan for the range
    elsif ( $words[0] eq "RANGE" ){
        $number2 = $words[1];
        next;
    }

    else{ 
        # store output of the program in array       
        my @c_output = split /\n/, `FindEven.out $number1 $number2`;
        my $op_format = 0;
        
        if ( $words[0] eq "ERROR_OUTPUT" ){
            @c_output = split / /, $c_output[0];
            @words = @words[1 .. $#words];
            $op_format = 1;      # for the string output flag the condition
        }

        print "Actual output:\t@c_output\n";
        
        print "Expected output:\t@words\n";
        
        validate_output(\@c_output, \@words, $op_format) ;
    }
}
