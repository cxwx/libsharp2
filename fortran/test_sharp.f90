!  This file is part of libsharp2.
!
!  libsharp2 is free software; you can redistribute it and/or modify
!  it under the terms of the GNU General Public License as published by
!  the Free Software Foundation; either version 2 of the License, or
!  (at your option) any later version.
!
!  libsharp2 is distributed in the hope that it will be useful,
!  but WITHOUT ANY WARRANTY; without even the implied warranty of
!  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!  GNU General Public License for more details.
!
!  You should have received a copy of the GNU General Public License
!  along with libsharp2; if not, write to the Free Software
!  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

!  libsharp2 is being developed at the Max-Planck-Institut fuer Astrophysik

!  \file test_sharp.f90
!  Demo Fortran code
!
!  Copyright (C) 2019 Max-Planck-Society
!  \author Martin Reinecke

program test_sharp
  use mpi
  use sharp
  use iso_c_binding, only : c_ptr, c_double
  implicit none

  integer, parameter :: lmax = 2, nside = 2
  type(sharp_alm_info) :: alm_info
  type(sharp_geom_info) :: geom_info

  real(c_double), dimension(0:(lmax + 1)**2 - 1, 1:1) :: alm
  real(c_double), dimension(0:12*nside**2 - 1, 1:1) :: map

  integer(c_int), dimension(1:lmax + 1) :: ms
  integer(c_int), dimension(1:4 * nside - 1) :: rings
  integer(c_int) :: nm, m, nrings, iring
  integer :: nodecount, rank, ierr

  call MPI_Init(ierr)
  call MPI_Comm_size(MPI_COMM_WORLD, nodecount, ierr)
  call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)

  nm = 0
  do m = rank, lmax, nodecount
     nm = nm + 1
     ms(nm) = m
  end do

  nrings = 0
  do iring = rank + 1, 4 * nside - 1, nodecount
     nrings = nrings + 1
     rings(nrings) = iring
  end do

  alm = 0
  map = 0
  if (rank == 0) then
    alm(0, 1) = 1
  end if

  print *, ms(1:nm)
  call sharp_make_mmajor_real_packed_alm_info(lmax, ms=ms(1:nm), alm_info=alm_info)
  print *, 'alm_info%n_local', alm_info%n_local
  call sharp_make_healpix_geom_info(nside, rings=rings(1:nrings), geom_info=geom_info)
  print *, 'geom_info%n_local', geom_info%n_local
  print *, 'execute'
  call sharp_execute(SHARP_Y, 0, 1, alm, alm_info, map, geom_info, comm=MPI_COMM_WORLD)

  print *, alm
  print *, map

  call sharp_destroy_alm_info(alm_info)
  call sharp_destroy_geom_info(geom_info)
  print *, 'DONE'
  call MPI_Finalize(ierr)
end program test_sharp
