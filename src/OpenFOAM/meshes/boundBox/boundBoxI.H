/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/boundBox/boundBox.H"
#include "OpenFOAM-2.1.x/src/OpenFOAM/meshes/primitiveShapes/point/pointField.H"


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline Foam::boundBox::boundBox()
:
    min_(point::zero),
    max_(point::zero)
{}


inline Foam::boundBox::boundBox(const point& min, const point& max)
:
    min_(min),
    max_(max)
{}


inline Foam::boundBox::boundBox(Istream& is)
{
    operator>>(is, *this);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const Foam::point& Foam::boundBox::min() const
{
    return min_;
}


inline const Foam::point& Foam::boundBox::max() const
{
    return max_;
}


inline Foam::point& Foam::boundBox::min()
{
    return min_;
}


inline Foam::point& Foam::boundBox::max()
{
    return max_;
}


inline Foam::point Foam::boundBox::midpoint() const
{
    return 0.5 * (max_ + min_);
}


inline Foam::vector Foam::boundBox::span() const
{
    return (max_ - min_);
}


inline Foam::scalar Foam::boundBox::mag() const
{
    return ::Foam::mag(max_ - min_);
}


inline Foam::scalar Foam::boundBox::volume() const
{
    return cmptProduct(span());
}


inline Foam::scalar Foam::boundBox::minDim() const
{
    return cmptMin(span());
}


inline Foam::scalar Foam::boundBox::maxDim() const
{
    return cmptMax(span());
}


inline Foam::scalar Foam::boundBox::avgDim() const
{
    return cmptAv(span());
}


inline bool Foam::boundBox::overlaps(const boundBox& bb) const
{
    return
    (
        bb.max_.x() >= min_.x() && bb.min_.x() <= max_.x()
     && bb.max_.y() >= min_.y() && bb.min_.y() <= max_.y()
     && bb.max_.z() >= min_.z() && bb.min_.z() <= max_.z()
    );
}


inline bool Foam::boundBox::contains(const point& pt) const
{
    return
    (
        pt.x() >= min_.x() && pt.x() <= max_.x()
     && pt.y() >= min_.y() && pt.y() <= max_.y()
     && pt.z() >= min_.z() && pt.z() <= max_.z()
    );
}


// this.bb fully contains bb
inline bool Foam::boundBox::contains(const boundBox& bb) const
{
    return contains(bb.min()) && contains(bb.max());
}


inline bool Foam::boundBox::containsInside(const point& pt) const
{
    return
    (
        pt.x() > min_.x() && pt.x() < max_.x()
     && pt.y() > min_.y() && pt.y() < max_.y()
     && pt.z() > min_.z() && pt.z() < max_.z()
    );
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

inline bool Foam::operator==(const boundBox& a, const boundBox& b)
{
    return (a.min_ == b.min_) && (a.max_ == b.max_);
}


inline bool Foam::operator!=(const boundBox& a, const boundBox& b)
{
    return !(a == b);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
