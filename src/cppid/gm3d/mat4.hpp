#ifndef CPPID_GM3D_MAT4_HPP
#define CPPID_GM3D_MAT4_HPP

#include <cmath>
#include <type_traits>
#include <utility>

#include <boost/qvm/all.hpp>

#include "vector_2d.hpp"
#include "vector_3d.hpp"

namespace cppid::gm3d {

template<typename T>
struct mat4 {
  T m[16];

  constexpr mat4() noexcept = default;

  explicit constexpr mat4(T s) noexcept
  : mat4{s, 0, 0, 0, 0, s, 0, 0, 0, 0, s, 0, 0, 0, 0, s}
  {
  }

  constexpr mat4(T m00,
                 T m01,
                 T m02,
                 T m03,
                 T m10,
                 T m11,
                 T m12,
                 T m13,
                 T m20,
                 T m21,
                 T m22,
                 T m23,
                 T m30,
                 T m31,
                 T m32,
                 T m33) noexcept
  : m{m00,
      m01,
      m02,
      m03,
      m10,
      m11,
      m12,
      m13,
      m20,
      m21,
      m22,
      m23,
      m30,
      m31,
      m32,
      m33}
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            !std::is_convertible_v<U, T>>* = nullptr>
  explicit constexpr mat4(const mat4<U>& m) noexcept
  : mat4(m.m[0],
         m.m[1],
         m.m[2],
         m.m[3],
         m.m[4],
         m.m[5],
         m.m[6],
         m.m[7],
         m.m[8],
         m.m[9],
         m.m[10],
         m.m[11],
         m.m[12],
         m.m[13],
         m.m[14],
         m.m[15])
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            std::is_convertible_v<U, T>>* = nullptr>
  explicit constexpr mat4(const mat4<U>& m) noexcept
  : mat4(m.m[0],
         m.m[1],
         m.m[2],
         m.m[3],
         m.m[4],
         m.m[5],
         m.m[6],
         m.m[7],
         m.m[8],
         m.m[9],
         m.m[10],
         m.m[11],
         m.m[12],
         m.m[13],
         m.m[14],
         m.m[15])
  {
  }

  constexpr auto operator*=(const mat4& m4) noexcept -> mat4&
  {
    const auto m00 = m[0], m01 = m[1], m02 = m[2], m03 = m[3], m10 = m[4],
               m11 = m[5], m12 = m[6], m13 = m[7], m20 = m[8], m21 = m[9],
               m22 = m[10], m23 = m[11], m30 = m[12], m31 = m[13], m32 = m[14],
               m33 = m[15];

    const auto n00 = m4.m[0], n01 = m4.m[1], n02 = m4.m[2], n03 = m4.m[3],
               n10 = m4.m[4], n11 = m4.m[5], n12 = m4.m[6], n13 = m4.m[7],
               n20 = m4.m[8], n21 = m4.m[9], n22 = m4.m[10], n23 = m4.m[11],
               n30 = m4.m[12], n31 = m4.m[13], n32 = m4.m[14], n33 = m4.m[15];

    m[0] = m00 * n00 + m01 * n10 + m02 * n20 + m03 * n30;
    m[1] = m00 * n01 + m01 * n11 + m02 * n21 + m03 * n31;
    m[2] = m00 * n02 + m01 * n12 + m02 * n22 + m03 * n32;
    m[3] = m00 * n03 + m01 * n13 + m02 * n23 + m03 * n33;
    m[4] = m10 * n00 + m11 * n10 + m12 * n20 + m13 * n30;
    m[5] = m10 * n01 + m11 * n11 + m12 * n21 + m13 * n31;
    m[6] = m10 * n02 + m11 * n12 + m12 * n22 + m13 * n32;
    m[7] = m10 * n03 + m11 * n13 + m12 * n23 + m13 * n33;
    m[8] = m20 * n00 + m21 * n10 + m22 * n20 + m23 * n30;
    m[9] = m20 * n01 + m21 * n11 + m22 * n21 + m23 * n31;
    m[10] = m20 * n02 + m21 * n12 + m22 * n22 + m23 * n32;
    m[11] = m20 * n03 + m21 * n13 + m22 * n23 + m23 * n33;
    m[12] = m30 * n00 + m31 * n10 + m32 * n20 + m33 * n30;
    m[13] = m30 * n01 + m31 * n11 + m32 * n21 + m33 * n31;
    m[14] = m30 * n02 + m31 * n12 + m32 * n22 + m33 * n32;
    m[15] = m30 * n03 + m31 * n13 + m32 * n23 + m33 * n33;

    return *this;
  }

  constexpr auto operator*(const mat4& m4) const noexcept -> mat4
  {
    return mat4{*this} *= m4;
  }

  constexpr auto operator*=(T s) noexcept -> mat4&
  {
    m[0] *= s;
    m[1] *= s;
    m[2] *= s;
    m[3] *= s;
    m[4] *= s;
    m[5] *= s;
    m[6] *= s;
    m[7] *= s;
    m[8] *= s;
    m[9] *= s;
    m[10] *= s;
    m[11] *= s;
    m[12] *= s;
    m[13] *= s;
    m[14] *= s;
    m[15] *= s;

    return *this;
  }

  constexpr auto operator*(T s) const noexcept -> mat4
  {
    return mat4{*this} *= s;
  }

  constexpr void m00(T val) noexcept
  {
    m[0] = val;
  }

  constexpr void m01(T val) noexcept
  {
    m[1] = val;
  }

  constexpr void m02(T val) noexcept
  {
    m[2] = val;
  }

  constexpr void m03(T val) noexcept
  {
    m[3] = val;
  }

  constexpr void m10(T val) noexcept
  {
    m[4] = val;
  }

  constexpr void m11(T val) noexcept
  {
    m[5] = val;
  }

  constexpr void m12(T val) noexcept
  {
    m[6] = val;
  }

  constexpr void m13(T val) noexcept
  {
    m[7] = val;
  }

  constexpr void m20(T val) noexcept
  {
    m[8] = val;
  }

  constexpr void m21(T val) noexcept
  {
    m[9] = val;
  }

  constexpr void m22(T val) noexcept
  {
    m[10] = val;
  }

  constexpr void m23(T val) noexcept
  {
    m[11] = val;
  }

  constexpr void m30(T val) noexcept
  {
    m[12] = val;
  }

  constexpr void m31(T val) noexcept
  {
    m[13] = val;
  }

  constexpr void m32(T val) noexcept
  {
    m[14] = val;
  }

  constexpr void m33(T val) noexcept
  {
    m[15] = val;
  }

  constexpr auto m00() const noexcept -> T
  {
    return m[0];
  }

  constexpr auto m01() const noexcept -> T
  {
    return m[1];
  }

  constexpr auto m02() const noexcept -> T
  {
    return m[2];
  }

  constexpr auto m03() const noexcept -> T
  {
    return m[3];
  }

  constexpr auto m10() const noexcept -> T
  {
    return m[4];
  }

  constexpr auto m11() const noexcept -> T
  {
    return m[5];
  }

  constexpr auto m12() const noexcept -> T
  {
    return m[6];
  }

  constexpr auto m13() const noexcept -> T
  {
    return m[7];
  }

  constexpr auto m20() const noexcept -> T
  {
    return m[8];
  }

  constexpr auto m21() const noexcept -> T
  {
    return m[9];
  }

  constexpr auto m22() const noexcept -> T
  {
    return m[10];
  }

  constexpr auto m23() const noexcept -> T
  {
    return m[11];
  }

  constexpr auto m30() const noexcept -> T
  {
    return m[12];
  }

  constexpr auto m31() const noexcept -> T
  {
    return m[13];
  }

  constexpr auto m32() const noexcept -> T
  {
    return m[14];
  }

  constexpr auto m33() const noexcept -> T
  {
    return m[15];
  }

  constexpr auto scale(T s) noexcept -> mat4&
  {
    return scale(s, s, s);
  }

  constexpr auto scale(const vector_3d<T>& v) noexcept -> mat4&
  {
    return scale(v.x(), v.y(), v.z());
  }

  constexpr auto scale(T x, T y, T z) noexcept -> mat4&
  {
    m[0] *= x;
    m[5] *= y;
    m[10] *= z;
    return *this;
  }

  constexpr auto identity() noexcept -> mat4&
  {
    boost::qvm::set_identity(*this);
    return *this;
  }

  constexpr auto rotate(const vector_3d<T>& origin, T a) noexcept -> mat4&
  {
    boost::qvm::rotate(*this, origin, a);
    return *this;
  }

  constexpr auto translate(T x, T y, T z) noexcept -> mat4&
  {
    const auto m03 = m[3];
    const auto m13 = m[7];
    const auto m23 = m[11];
    const auto m33 = m[15];

    m[0] += m03 * x;
    m[4] += m13 * x;
    m[8] += m23 * x;
    m[12] += m33 * x;

    m[1] += m03 * y;
    m[5] += m13 * y;
    m[9] += m23 * y;
    m[13] += m33 * y;

    m[2] += m03 * z;
    m[6] += m13 * z;
    m[10] += m23 * z;
    m[14] += m33 * z;

    return *this;
  }

  constexpr auto translate(const vector_3d<T>& v) noexcept -> mat4&
  {
    return translate(v.x(), v.y(), v.z());
  }

  constexpr auto frustum(T l, T r, T b, T t, T n, T f) noexcept -> mat4&
  {
    m[0] = 2 * n / (r - l);
    m[5] = 2 * n / (t - b);
    m[8] = (r + l) / (r - l);
    m[9] = (t + b) / (t - b);
    m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[12] = m[13] = m[15] = 0;
    m[11] = -1;

    if(std::isfinite(f)) {
      m[10] = -(f + n) / (f - n);
      m[14] = -(2 * f * n) / (f - n);
    } else {
      m[10] = -1;
      m[14] = -2 * n;
    }

    return *this;
  }

  constexpr auto orthogonal(T l, T r, T b, T t, T n, T f) noexcept -> mat4&
  {
    m[0] = 2 / (r - l);
    m[5] = 2 / (t - b);
    m[10] = -2 / (f - n);
    m[11] = 0;
    m[12] = -(l + r) / (r - l);
    m[13] = -(t + b) / (t - b);
    m[14] = -(f + n) / (f - n);
    m[15] = 1;
    m[6] = m[7] = m[8] = m[9] = m[1] = m[2] = m[3] = m[4] = 0;

    return *this;
  }

  constexpr auto
  lookat(T ex, T ey, T ez, T lx, T ly, T lz, T ux, T uy, T uz) noexcept -> mat4&
  {
    auto fx = ex - lx;
    auto fy = ey - ly;
    auto fz = ez - lz;
    const auto fl = std::sqrt(fx * fx + fy * fy + fz * fz);
    fx /= fl;
    fy /= fl;
    fz /= fl;

    const auto ul = std::sqrt(ux * ux + uy * uy + uz * uz);
    ux /= ul;
    uy /= ul;
    uz /= ul;

    const auto rx = uy * fz - uz * fy;
    const auto ry = uz * fx - ux * fz;
    const auto rz = ux * fy - uy * fx;

    ux = fy * rz - fz * ry;
    uy = fz * rx - fx * rz;
    uz = fx * ry - fy * rx;

    m[0] = rx;
    m[1] = ux;
    m[2] = fx;
    m[3] = 0;

    m[4] = ry;
    m[5] = uy;
    m[6] = fy;
    m[7] = 0;

    m[8] = rz;
    m[9] = uz;
    m[10] = fz;
    m[11] = 0;

    m[12] = -(rx * ex + ry * ey + rz * ez);
    m[13] = -(ux * ex + uy * ey + uz * ez);
    m[14] = -(fx * ex + fy * ey + fz * ez);
    m[15] = 1;
    return *this;
  }

  constexpr auto lookat(vector_3d<T> e, vector_3d<T> l, vector_3d<T> u) noexcept
   -> mat4&
  {
    return lookat(
     e.x(), e.y(), e.z(), l.x(), l.y(), l.z(), u.x(), u.y(), u.z());
  }

  constexpr auto perspective(T fov, T a, T n, T f) noexcept -> mat4&
  {
    return *this = boost::qvm::perspective_rh(fov, a, n, f);
  }

  constexpr auto is_invertible() const noexcept -> bool
  {
    return determinant() != T{0};
  }

  constexpr auto inverse() noexcept -> mat4&
  {
    return *this = boost::qvm::inverse(*this);
  }

  constexpr auto transpose() noexcept -> mat4&
  {
    *this = {m[0],
             m[4],
             m[8],
             m[12],
             m[1],
             m[5],
             m[9],
             m[13],
             m[2],
             m[6],
             m[10],
             m[14],
             m[3],
             m[7],
             m[11],
             m[15]};

    return *this;
  }

  auto determinant() const noexcept -> bool
  {
    return boost::qvm::determinant(*this);
  }
};

} // namespace cppid::gm3d

namespace boost::qvm {
template<class T>
struct mat_traits<cppid::gm3d::mat4<T>> {
  using scalar_type = T;
  static int const rows = 4;
  static int const cols = 4;

  template<int Row, int Col>
  static constexpr auto read_element(cppid::gm3d::mat4<scalar_type> const& x)
   -> scalar_type
  {
    return x.m[Row * 4 + Col];
  }

  template<int Row, int Col>
  static constexpr auto write_element(cppid::gm3d::mat4<scalar_type>& x)
   -> scalar_type&
  {
    return x.m[Row * 4 + Col];
  }

  static constexpr auto
  read_element_idx(int row, int col, cppid::gm3d::mat4<scalar_type> const& x)
   -> scalar_type
  {
    return x.m[row * 4 + col];
  }

  static constexpr auto
  write_element_idx(int row, int col, cppid::gm3d::mat4<scalar_type>& x)
   -> scalar_type
  {
    return x.m[row * 4 + col];
  }
};
} // namespace boost::qvm

#endif
