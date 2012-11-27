/*
//@HEADER
// ************************************************************************
// 
//   KokkosArray: Manycore Performance-Portable Multidimensional Arrays
//              Copyright (2012) Sandia Corporation
// 
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact  H. Carter Edwards (hcedwar@sandia.gov) 
// 
// ************************************************************************
//@HEADER
*/

#ifndef KOKKOSARRAY_CUDA_ABORT_HPP
#define KOKKOSARRAY_CUDA_ABORT_HPP

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

#if defined( __CUDACC__ ) && defined( __CUDA_ARCH__ ) && \
    defined( CUDA_RELEASE_VERSION ) && \
    ( 401 <= CUDA_RELEASE_VERSION )

extern "C" {
/*  Cuda runtime function, declared in <crt/device_runtime.h>
 *  Requires capability 2.x or better.
 */
extern __device__ void __assertfail(
  const void  *message,
  const void  *file,
  unsigned int line,
  const void  *function,
  size_t       charsize);
}

namespace KokkosArray {

__device__ inline
void cuda_abort( const char * const message )
{
  const char empty[] = "" ;

  __assertfail( (const void *) message ,
                (const void *) empty ,
                (unsigned int) 0 ,
                (const void *) empty ,
                sizeof(char) );
}

} // namespace KokkosArray

#else

namespace KokkosArray {
KOKKOSARRAY_INLINE_FUNCTION
void cuda_abort( const char * const ) {}
}

#endif /* #if defined( __CUDACC__ ) && defined( __CUDA_ARCH__ ) */

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

#endif /* #ifndef KOKKOSARRAY_CUDA_ABORT_HPP */
