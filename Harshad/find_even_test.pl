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
# OTP_SIZE - size of OTP
# PUBLIC_TOKEN_ID - public token id used to access the secret on server
# SECRET - base 64 secret used to generage HOTP
# MOVING_FACTOR - initial sequence number for a given token id
# MAX_FAILED_ATTEMPTS - no. of failed attempts tolerated
# UNBLOCK  - Unblock <public_token_id> and reset no_of_failed_attempts
# AUTH_WINDOW  - Set look ahead window size
# SLEEP - Halts the process for the mentioned duration of time
# ASSIGN_TOKEN - assigns <public_token_id> from grsoath_tokens from grsoathdb
# to <user> from ykmap database
#
# CAUTION:
# ------------------------------------------------------------------------------
# Program does not validate the sequence of input in the test data.
# It is upto the tester to build the test case hence the tester has full flex-
# -bility to enter data in the sequence (s)he decides
#-------------------------------------------------------------------------------

use strict;
use warnings;

open my $test_data, "<", "/home/harshad/dump/text-files/find_test.txt" or 
    die "Can't open data file $!";
open my $test_log, ">", "/home/harshad/dump/test-scripts/find_test_log.txt" or
    die "Can't open log file $!";

my $number1 = 0;
my $number2 = 0;
my $log_id = 0;
    
foreach my $line ( <$test_data> ){

#    printf "\nIn while\n";
    my @words = split ' ', $line;
    
    if ( $words[0] eq '#' ){
        next ;
    }
    elsif ( $words[0] eq "NUMBER1" ){
        $number1 = $words[1];
        next;
    }
    elsif ( $words[0] eq "NUMBER2" ){
        $number2 = $words[1];
        next;
    }

    else{        
        my $result = `FindEven.out 1 3`;
        print "Result:\t$result\n";
        my @result = split /\n/, $result;
        print "Splitted result: @result";
        print "File line:\t@words\n";
#       =begin comment
#       my $flag = 0;
#       for ( my $i = 0; $i < @words; $i++ ){
#            if ( $words[$i] eq $result[$i] ){
#                $flag = 1;
#                next ;
#            }
#            else{
#                  $log_id++;
#                if ( $log_id == 1 ){
#                    print $test_log "\tId\t|\tTimestamp\t\t|\tentry\n";
#                    print $test_log "------------------------------------------",
#                       "---------------------------------------------------\n";
#               }
#               print $test_log "NUMBER1:\t", $number1, "\nNUMBER2:\t", $number2,
#                                "\n";
#               print $test_log "\t", $log_id, "\t|", "\t", localtime(),
#                                "\t|", "\t", "Test Failed\n";
#               $flag = 0;
#               last ;
#            }
#       }
#
#       if ( $flag == 1){
#           $log_id++;
#            if ( $log_id == 1 ){
#                print $test_log "\tId\t|\tTimestamp\t\t|\tentry\n";
#                print $test_log "------------------------------------------",
#                     "---------------------------------------------------\n";
#            }
#            print $test_log "NUMBER1:\t", $number1, "\nNUMBER2:\t", $number2,
#                            "\n";
#            print $test_log "\t", $log_id, "\t|", "\t", localtime(),
#                            "\t|", "\t", "Test Passed\n";
#       }
#       =end comment
#       =cut
    }
}
 
print "Closing files\n";
 
close $test_data;
close $test_log;
