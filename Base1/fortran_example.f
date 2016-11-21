  program main

c*********************************************************************72
c
cc MAIN is the main program for F77_INTRINSICS.
c
c  Discussion:
c
c    F77_INTRINSICS tests FORTRAN77 intrinsic routines.
c
c  Licensing:
c
c    This code is distributed under the GNU LGPL license.
c
c  Modified:
c
c    02 June 2007
c
c  Author:
c
c    John Burkardt
c
      implicit none

      call timestamp ( )

      write ( *, '(a)' ) ' '
      write ( *, '(a)' ) 'F77_INTRINSICS'
      write ( *, '(a)' ) '  FORTRAN77 version'
      write ( *, '(a)' ) '  Test FORTRAN77 intrinsic library.'

      call test_abs
      call test_acos
      call test_aimag
      call test_aint
      call test_anint
      call test_asin
      call test_atan
      call test_atan2
      call test_btest
      call test_char
      call test_cmplx
      call test_conjg
      call test_cos_c4
      call test_cos_r8
      call test_cosh
      call test_dble
      call test_dim
      call test_dprod
      call test_exp
      call test_iand_i4
      call test_ibclr
      call test_ibits
      call test_ibset
      call test_ichar
      call test_ieor_i4
      call test_index
      call test_int
      call test_ior_i4
      call test_ishft
      call test_ishftc
      call test_len
      call test_len_trim
      call test_lge
      call test_lgt
      call test_lle
      call test_llt
      call test_log
      call test_log10
      call test_max
      call test_min
      call test_mod_i4
      call test_mod_r4
      call test_mvbits
      call test_nint
      call test_not_i4
      call test_real_c4
      call test_sign
      call test_sin_r8
      call test_sinh
      call test_sqrt
      call test_tan
      call test_tanh
c
c  Terminate.
c
      write ( *, '(a)' ) ' '
      write ( *, '(a)' ) 'F77_INTRINSICS'
      write ( *, '(a)' ) '  Normal end of execution.'

      write ( *, '(a)' ) ' '
      call timestamp ( )

      stop
      end

function test_abs()

c*********************************************************************72
c
cc TEST_ABS tests ABS.
c
c  Discussion:
c
c    The FORTRAN77 function ABS returns the absolute value of a
c    number.  For complex numbers, this is the magnitude.
c
c  Licensing:
c
c    This code is distributed under the GNU LGPL license.
c
c  Modified:
c
c    02 June 2007
c
c  Author:
c
c    John Burkardt
c
      implicit none

      complex c4
      integer i4
      real r4
      double precision r8

      c4 = ( 1.0E+00, -2.0E+00 )
      i4 = -88
      r4 = 45.78E+00
      r8 = 45.78D+00

      write ( *, '(a)' ) ' '
      write ( *, '(a)' ) 'TEST_ABS'
      write ( *, '(a)' ) '  ABS is a FORTRAN77 function which returns'
      write ( *, '(a)' ) '  the absolute value of a numeric quantity'
      write ( *, '(a)' ) ' '
      write ( *, '(a)' )
     & '      Type                  VALUE                ABS(VALUE)'
      write ( *, '(a)' ) ' '
      write ( *, '(a,i12,12x,i12)' )
     &     '  integer              ', i4, abs ( i4 )
      write ( *, '(a,f12.4,12x,f12.4)' )
     & '  Real                 ', r4, abs ( r4 )
      write ( *, '(a,f12.4,12x,f12.4)' )
     & '  Double precision     ', r8, abs ( r8 )
      write ( *, '(a,2f12.4,f12.4)' )
     &  '  Complex              ', c4, abs ( c4 )

      return
      end function 






function second()

c*********************************************************************72
c  Discussion:
c
c    The FORTRAN77 function ABS returns the absolute value of a
c    number.  For complex numbers, this is the magnitude.
c
c  Licensing:
c
c    This code is distributed under the GNU LGPL license.
c
c  Modified:
c
c    02 June 2007
c
c  Author:
c
c    John Burkardt
c
      implicit none

      complex c4
      integer i4
      real r4
      double precision r8

      c4 = ( 1.0E+00, -2.0E+00 )
      i4 = -88
      r4 = 45.78E+00
      r8 = 45.78D+00

      write ( *, '(a)' ) ' '
      write ( *, '(a)' ) 'TEST_ABS'
      write ( *, '(a)' ) '  ABS is a FORTRAN77 function which returns'
      write ( *, '(a)' ) '  the absolute value of a numeric quantity'
      write ( *, '(a)' ) ' '
      write ( *, '(a)' )
     & '      Type                  VALUE                ABS(VALUE)'
      write ( *, '(a)' ) ' '
      write ( *, '(a,i12,12x,i12)' )
     &     '  integer              ', i4, abs ( i4 )
      write ( *, '(a,f12.4,12x,f12.4)' )
     & '  Real                 ', r4, abs ( r4 )
      write ( *, '(a,f12.4,12x,f12.4)' )
     & '  Double precision     ', r8, abs ( r8 )
      write ( *, '(a,2f12.4,f12.4)' )
     &  '  Complex              ', c4, abs ( c4 )

      return
      end function 