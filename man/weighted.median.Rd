\name{weighted.median}
\alias{weighted.median}

\title{Weighted Median Value}

\usage{weighted.median(x, w, na.rm=TRUE, ties=NULL)}

\description{
  Compute a weighted median of a numeric vector.
}

\arguments{
  \item{x}{a numeric vector containing the values whose weighted median is
    to be computed.}
  \item{w}{a vector of weights the same length as \code{x} giving the weights
    to use for each element of \code{x}. Default value is equal weight
    to all values.}
  \item{na.rm}{a logical value indicating whether \code{NA} values in
    \code{x} should be stripped before the computation proceeds.}
  \item{ties}{a character string specifying how to solve ties between two
    \code{x}'s that are satisfying the weighted median criteria.
    Note that at most two values can satisfy the criteria.
    When \code{ties} is \code{"min"}, the smaller value of the two
    is returned and when it is \code{"max"}, the larger value is
    returned.
    If \code{ties} is \code{"mean"}, the mean of the two values is
    returned and if it is \code{"both"}, both values are returned.
    Finally, if \code{ties} is \code{"weighted"} (or \code{NULL}) a
    weighted average of the two are returned, where the weights are
    weights of all values \code{x[i] <= x[k]} and \code{x[i] >= x[k]},
    respectively. Default value is \code{NULL}.}
}

\value{
  Returns the weighted median.
}

\details{
  For the \code{n} elements \code{x = c(x[1], x[2], ..., x[n])} with positive
  weights \code{w = c(w[1], w[2], ..., w[n])} such that \code{sum(w) = S},
  the \emph{weighted median} is defined as the element \code{x[k]} for which
  initial  the total weight of all elements \code{x[i] < x[k]} is less or equal to
  \code{S/2} and for which the total weight of all elements
  \code{x[i] > x[k]} is less or equal to \code{S/2} (c.f. [1]).
  
  If \code{w} is missing then all elements of \code{x} are given the same
  positive weight. If all weights are zero, \code{NA} is returned.
  
  When all the weights are the same and \code{ties} is \code{"weighted"} (or
  \code{NULL}) \code{weighted.median} gives the same result as \code{median}.
  
  If one or more weights are \code{Inf}, it is the same as these weights
  have the same weight and the others has zero. This makes things easier for
  cases where the weights are result of a division with zero.
  
  The weighted median solves the following optimization problem:
  
  \deqn{\alpha^* = \arg_\alpha \min \sum_{k=1}{K} w_k |x_k-\alpha|}
  where \eqn{x=(x_1,x_2,\ldots,x_K)} are scalars and
  \eqn{w=(w_1,w_2,\ldots,w_K)} are the corresponding "weights" for
  each individual \eqn{x} value.
}

\examples{
   x <- 1:10
   n <- length(x)
   median(x)                            # 5.5
   weighted.median(x)                   # 5.5
   w <- rep(1, n)
   weighted.median(x, w)                # 5.5 (default)
   weighted.median(x, ties="weighted")  # 5.5 (default)
   weighted.median(x, ties="min")       # 5
   weighted.median(x, ties="max")       # 6

   # Pull the median towards zero
   w[1] <- 5
   weighted.median(x, w)                # 3.5
   y <- c(rep(0,w[1]), x[-1])           # Only possible for integer weights
   median(y)                            # 3.5

   # Put even more weight on the zero
   w[1] <- 8.5
   weighted.median(x, w)                # 2

   # All weight on the first value
   w[1] <- Inf
   weighted.median(x, w)                # 1

   # All weight on the first value
   w[1] <- 1
   w[n] <- Inf
   weighted.median(x, w)                # 10

   # All weights set to zero
   w <- rep(0, n)
   weighted.median(x, w)                # NA
 }

 \seealso{
   \code{\link[base]{median}}, \code{\link[base]{mean}} and
   \code{\link[base]{weighted.mean}}
 }
 
 \references{
   [1]  T.H. Cormen, C.E. Leiserson, R.L. Rivest, Introduction to Algorithms,
   The MIT Press, Massachusetts Institute of Technology, 1989.
 }
 
 \author{Henrik Bengtsson, hb at maths.lth.se with help from
   Roger Koenker, roger at ysidro.econ.uiuc.edu}
 
