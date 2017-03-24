#  Copyright (c) 1997-2015
#  Ewgenij Gawrilow, Michael Joswig (Technische Universitaet Berlin, Germany)
#  http://www.polymake.org
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by the
#  Free Software Foundation; either version 2, or (at your option) any
#  later version: http://www.gnu.org/licenses/gpl.txt.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#-------------------------------------------------------------------------------

@make_vars=qw( BundledSympol CXXflags LDflags SympolLib );

sub allowed_options {
   my ($allowed_options, $allowed_with)=@_;
   @$allowed_with{ qw( sympol sympol-include sympol-lib ) }=();
}

sub usage {
   print STDERR "  --with-sympol=PATH          Installation path of sympol, if non-standard.\n",
                "                              Without this option polymake will try to use a systemwide\n",
                "                              installation or fall back to the bundled sympol\n",
                "                              (bundled/sympol/external/sympol) if it exists.\n",
                "                              To force the bundled version 'bundled' can be given as option.\n";
                "  --with-sympol-include=PATH  Path to the folder containing symmetrycomputation.h.  \n",
                "  --with-sympol-lib=PATH      Path to the folder containing libsympol.{a,so,dylib} \n";

}

sub check_bundled {
   -e "bundled/sympol/external/sympol/sympol/symmetrycomputation.h"
}

sub proceed {
   my ($options)=@_;
   my $sympol_path;
   $BundledSympol = "yes";

   if (defined ($sympol_path=$options->{sympol}) and $sympol_path ne "bundled") {
      if (-f "$sympol_path/include/sympol/symmetrycomputation.h") {
         $CXXflags .= " -I$sympol_path/include";
      }
      my $sympol_lib=Polymake::Configure::get_libdir($sympol_path, "sympol");
      if (-f "$sympol_lib/libsympol.$Config::Config{so}" ) {
         $LDflags = "-L$sympol_lib";
         $LDflags .= " -Wl,-rpath,$sympol_lib" unless ($sympol_path eq "/usr");
      }
      if (!$CXXflags or !$LDflags) {
         die "Invalid installation location of sympol: header file symmetrycomputation.h and/or library libsympol.$Config::Config{so} not found.\n",
             "You might try to use --with-sympol-include and --with-sympol-lib.\n";

      }
   }
   if (defined (my $sympol_inc=$options->{'sympol-include'})) {
      $CXXflags .=" -I$sympol_inc";
      $sympol_path .= "include: $sympol_inc ";
   }
   if (defined ($sympol_lib=$options->{'sympol-lib'})) {
      $LDflags = " -L$sympol_lib";
      $LDflags .= " -Wl,-rpath,$sympol_lib" unless ($sympol_lib =~ m#^/usr/lib#);
      $sympol_path .= "lib: $sympol_lib";
   }

   if ($Polymake::Bundled::lrs::BundledLrs eq "yes" or $Polymake::Bundled::cdd::BundledCdd eq "yes" or $Polymake::Configure::ExternalHeaders =~ /permlib/) {
      if (defined($sympol_path) and $sympol_path ne "bundled") {
         die "Using a non-bundled sympol configuration requires non-bundled lrs, cdd and PermLib as well.\n",
             "Please use --with-cdd=PATH, --with-lrs=PATH and --with-permlib=PATH or remove the --with-sympol option.\n";
      }
      $sympol_path = "bundled";
   }

   if ($sympol_path ne "bundled") {
      my $testcode = <<"---";
#include <cstddef>
#include <iostream>
#include <gmpxx.h>
#include <sympol/polyhedron.h>

int main() {
   boost::shared_ptr<sympol::PermutationGroup> pg;
   return 0;
}
---
      my $error=Polymake::Configure::build_test_program($testcode, Libs => "-lsympol", CXXflags => "$CXXflags", LDflags => "$LDflags");
      if ($?==0) {
         my $message=Polymake::Configure::run_test_program();
         if ($?) {
            check_bundled() and !defined($sympol_path) or 
               die "Could not run a test program checking for sympol library.\n",
                   "The complete error log follows:\n\n$message\n",
                   "Please investigate the reasons and fix the installation.\n";
         } else {
            $BundledSympol = undef;
         }
      } else {
         check_bundled() and !defined($sympol_path) or 
            die "Could not compile a test program checking for sympol.\n",
                "The most probable reasons are that the library is installed at a non-standard location,\n",
                "is not configured to build a shared module, or missing at all.\n",
                "The complete error log follows:\n\n$error\n",
                "Please install the library and specify its location using --with-sympol option, if needed.\n",
      }
   } 


   if ($BundledSympol eq "yes") {
      # check GMP C++ bindings (only for bundled sympol)
      my $build_error=Polymake::Configure::build_test_program(<<'---', Libs => "$Polymake::Configure::ARCHFLAGS -lgmpxx -lgmp");
#include <cstddef>
#include <gmpxx.h>
#include <iostream>
int main() {
   mpq_class x(7,3);
   std::cout << __GNU_MP_VERSION << '.' << __GNU_MP_VERSION_MINOR << '.' << __GNU_MP_VERSION_PATCHLEVEL << std::flush;
   return 0;
}
---
      if ($?==0) {
         my $is_version=Polymake::Configure::run_test_program();
         if ($?==0) {
            if (Polymake::Configure::v_cmp($is_version,"4.2.0")<0) {
               die "The GNU Multiprecision Library (GMP) C++ bindings installed at your site are of version $is_version\n",
                   "while 4.2.0 is the minimal required version.\n",
                   "Since a more recent GMP installation was found, it was probably configured without --enable-cxx .\n";
            }
         } else {
            die "Could not run a test program linked to the C++ version of the GNU Multiprecision Library (GMP).\n",
                "Probably the shared library libgmpxx.$Config::Config{dlext} is missing or of an incompatible machine type.\n";
         }
      } else {
         die "Could not compile a test program checking for C++ bindings of the GNU Multiprecision Library (GMP).\n",
             "The most probable reasons are that a gmpxx package is missing, lacking the developer's subpackage \n",
             "or GMP was configured without C++ support (--enable-cxx).\n",
             "Please refer to the installation instructions at $Wiki/howto/install.\n",
             "The complete error log follows:\n", $build_error;
      }
   }

   if ($BundledSympol eq "yes") {
      die "bundled sympol requested but it cannot be found" 
         unless check_bundled();
      $CXXflags.=' -I$(ExtensionTop)/external/sympol';
      # Up to the main BuildDir to descent into the right extension
      # Mainly for the group extension.
      $SympolLib='${BuildDir}/../../bundled/sympol/staticlib/sympol/libsympol%A';
   } else {
      $SympolLib="-lsympol";
   }


   return $BundledSympol eq "yes" ? 
            "bundled" : 
            ($sympol_path//"system");

}
