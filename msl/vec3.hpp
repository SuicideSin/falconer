#ifndef MSL_VEC3_H
#define MSL_VEC3_H

namespace msl
{
	template <typename T> class vec3
	{
		public:
			vec3(const T& X,const T& Y,const T& Z):x(x),y(Y),z(Z)
			{}

		private:
			T x;
			T y;
			T z;
	};
}

#endif