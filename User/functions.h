#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "includes.h"
//float32_t sound_vec[VEC_LENGTH] = {2073,2067,2066,2075,2070,2070,2076,2078,2076,2077,2074,2071,2069,2076,2086,2070,2060,2075,2065,2062,2064,2074,2071,2080,2058,2058,2063,2060,2071,2062,2064,2063,2060,2064,2069,2067,2071,2066,2060,2072,2066,2065,2056,2044,2067,2079,2053,2065,2076,2064,2055,2044,2057,2061,2055,2035,2061,2057,2053,2033,2046,2063,2053,2043,2056,2066,2064,2057,2052,2069,2048,2046,2050,2045,2053,2053,2036,2065,2070,2040,2050,2042,2065,2047,2034,2054,2077,2044,2030,2050,2059,2061,2048,2047,2076,2061,2035,2098,2085,2025,2089,2092,2060,2078,2059,2080,2107,2023,2022,2064,2033,2036,2048,2034,2049,2034,2023,2067,2051,2014,2031,2020,2020,2032,1996,2025,2036,2018,2010,2031,2022,2032,2021,2035,2035,2037,2023,2024,2046,2038,2019,2025,2067,2061,2046,2071,2081,2086,2087,2078,2083,2100,2086,2093,2084,2082,2093,2088,2075,2089,2091,2086,2088,2066,2115,2086,2063,2058,2076,2074,2044,2023,2038,2042,2018,2000,2007,2032,2028,2007,2006,2005,2007,2011,2002,2010,1996,1996,1986,1984,1962,1965,1966,1996,2000,2021,2019,2040,2041,2078,2042,2041,2061,2093,2081,2085,2132,2144,2144,2161,2179,2174,2149,2130,2145,2142,2108,2092,2114,2124,2110,2093,2110,2137,2113,2077,2098,2094,2075,2036,2036,2041,2045,1979,1987,2024,2021,1996,1974,1958,1954,1955,1949,1922,1893,1901,1922,1924,1926,1963,1961,1993,2030,2051,2054,2070,2076,2095,2108,2105,2097,2105,2129,2139,2113,2137,2151,2157,2164,2175,2183,2173,2157,2149,2152,2140,2141,2130,2124,2149,2143,2123,2117,2113,2098,2077,2053,2055,2045,2007,2003,2011,1992,1951,1951,1934,1929,1886,1855,1847,1843,1840,1868,1904,1951,1988,2032,2058,2072,2074,2086,2084,2086,2066,2085,2123,2119,2115,2111,2137,2142,2125,2106,2123,2136,2124,2103,2112,2149,2167,2132,2130,2165,2156,2133,2122,2123,2126,2104,2079,2078,2090,2062,2035,2034,2010,1987,1981,1957,1937,1920,1880,1840,1804,1784,1813,1857,1902,1989,2029,2074,2104,2099,2098,2086,2045,2057,2083,2065,2097,2126,2124,2144,2135,2111,2127,2121,2091,2110,2102,2089,2099,2115,2110,2146,2155,2152,2160,2161,2122,2123,2094,2092,2088,2071,2072,2080,2060,2045,2031,1990,1966,1952,1899,1833,1832,1778,1745,1819,1876,1943,2045,2071,2101,2135,2126,2086,2072,2032,2033,2086,2049,2094,2127,2132,2145,2148,2115,2117,2094,2057,2060,2063,2057,2081,2097,2092,2113,2131,2141,2161,2152,2131,2140,2125,2099,2082,2079,2078,2086,2061,2065,2075,2061,2013,1974,1926,1879,1822,1759,1724,1785,1867,1974,2039,2105,2148,2172,2124,2067,2023,2027,2010,2024,2052,2106,2144,2155,2160,2165,2130,2079,2049,2032,2030,2034,2037,2066,2103,2119,2126,2144,2137,2104,2118,2129,2123,2111,2113,2119,2113,2094,2088,2098,2113,2104,2093,2077,2053,1997,1950,1897,1854,1764,1691,1703,1869,2009,2030,2097,2188,2231,2157,2056,2000,2022,1991,1986,2027,2116,2158,2174,2162,2175,2148,2075,2016,2019,2017,2012,2019,2068,2122,2139,2119,2135,2134,2108,2077,2093,2111,2088,2084,2152,2154,2124,2108,2126,2131,2131,2098,2097,2098,2070,1998,1955,1912,1832,1760,1694,1680,1839,1999,2034,2117,2211,2244,2163,2069,1997,2019,1986,1994,2040,2125,2164,2196,2170,2179,2144,2059,2000,2004,1996,2002,2027,2065,2115,2147,2130,2134,2139,2119,2072,2055,2051,2059,2051,2067,2127,2175,2192,2198,2174,2160,2142,2106,2063,2071,2045,2009,1973,1953,1899,1828,1742,1689,1756,1866,2013,2084,2152,2207,2234,2152,2072,2011,2021,2008,2023,2058,2134,2172,2175,2183,2145,2103,2051,1993,1985,1999,2013,2030,2071,2125,2148,2138,2123,2104,2083,2048,2039,2038,2078,2099,2119,2132,2173,2175,2163,2149,2151,2130,2106,2067,2053,2082,2042,2006,1968,1947,1908,1844,1768,1721,1686,1823,2008,2077,2119,2199,2255,2206,2095,2012,2004,2016,2019,2023,2083,2142,2167,2141,2122,2096,2060,1995,1981,1999,2028,2044,2060,2092,2126,2128,2102,2082,2074,2067,2052,2050,2068,2103,2166,2163,2105,2117,2156,2125,2084,2082,2122,2135,2092,2049,2056,2054,2017,1978,1966,1979,1947,1879,1835,1814,1732,1663,1870,2124,2145,2099,2208,2259,2199,2048,1953,1995,2040,2000,1995,2072,2152,2165,2113,2080,2111,2082,1984,1951,1999,2030,2038,2041,2088,2143,2150,2115,2105,2114,2098,2065,2044,2049,2065,2068,2070,2093,2129,2152,2130,2110,2129,2129,2100,2075,2074,2063,2052,2028,2011,2006,1993,1944,1911,1884,1850,1792,1720,1674,1855,2117,2161,2111,2205,2270,2233,2081,1973,1980,2043,1993,1958,2036,2129,2152,2135,2089,2111,2101,2020,1966,2000,2050,2087,2090,2111,2155,2167,2111,2052,2048,2051,2047,2027,2035,2083,2143,2136,2123,2138,2138,2103,2072,2046,2085,2104,2088,2077,2089,2083,2057,2017,1999,2011,2013,1997,1981,1990,1967,1944,1881,1834,1787,1743,1869,2106,2175,2117,2179,2215,2197,2072,1949,1918,2021,2022,2007,2058,2160,2215,2206,2118,2097,2102,2059,1983,1978,2025,2092,2112,2092,2115,2151,2140,2092,2054,2044,2057,2056,2034,2045,2090,2146,2137,2088,2074,2083,2054,2013,1997,2017,2079,2101,2098,2102,2125,2117,2093,2046,2046,2046,2048,2053,2011,2000,1978,1933,1878,1829,1784,1749,1682,1897,2139,2190,2127,2186,2217,2214,2096,1971,1980,2076,2099,2076,2083,2141,2214,2196,2082,2044,2060,2053,2021,1987,2016,2098,2140,2117,2098,2103,2111,2096,2033,1994,2021,2043,2035,2026,2047,2096,2152,2147,2100,2094,2113,2111,2087,2053,2056,2087,2091,2077,2066,2085,2096,2085,2043,2028,2032,2044,2043,2035,2028,2034,2031,1987,1947,1910,1872,1831,1781,1709,1935,2181,2220,2149,2162,2174,2186,2087,1940,1928,2033,2108,2111,2070,2098,2188,2200,2118,2041,2012,2038,2061,2022,1995,2052,2109,2123,2095,2062,2069,2104,2088,2046,2027,2044,2070,2071,2039,2026,2045,2086,2111,2092,2053,2078,2097,2099,2079,2075,2099,2145,2145,2121,2098,2099,2108,2090,2053,2029,2036,2044,2034,2004,1993,2004,2006,1984,1951,1935,1928,1916,1860,1777,1717,1834,2067,2198,2163,2138,2166,2208,2178,2054,1945,1979,2068,2125,2098,2065,2105,2161,2157,2091,2009,1979,2022,2055,2046,2031,2045,2084,2121,2111,2074,2059,2077,2094,2090,2060,2045,2067,2091,2106,2101,2099,2106,2132,2129,2096,2062,2060,2063,2067,2054,2043,2052,2058,2092,2091,2079,2064,2083,2083,2076,2053,2059,2075,2089,2070,2037,2020,2013,2012,2017,1951,1921,1920,1901,1868,1812,1768,1808,1960,2121,2196,2174,2144,2142,2162,2128,2050,1980,2003,2065,2123,2111,2078,2079,2116,2135,2111,2044,2009,2023,2064,2093,2086,2067,2076,2109,2132,2115,2071,2044,2059,2077,2079,2054,2039,2053,2084,2092,2073,2063,2058,2072,2095,2095,2059,2048,2051,2071,2082,2083,2081,2090,2110,2116,2107,2081,2067,2064,2076,2072,2071,2056,2058,2064,2065,2045,2025,2008,2005,2002,1984,1956,1930,1920,1890,1855,1803,1805,1871,2008,2116,2161,2151,2126,2113,2115,2116,2074,2028,2016,2069,2123,2147,2127,2107,2098,2102,2093,2066,2035,2030,2053,2083,2097,2089,2075,2069,2073,2069,2061,2045,2034,2034,2048,2057,2060,2055,2052,2065,2072,2081,2084,2083,2084,2107,2129,2127,2111,2088,2086,2088,2096,2078,2072,2071,2079,2072,2060,2058,2062,2065,2056,2051,2053,2056,2055,2052,2050,2045,2030,2000,1975,1959,1954,1944,1925,1901,1873,1838,1832,1880,1988,2082,2121,2117,2112,2118,2127,2134,2107,2071,2057,2063,2086,2108,2110,2098,2078,2060,2063,2076,2083,2080,2076,2076,2090,2093,2086,2075,2061,2049,2041,2036,2037,2029,2021,2027,2047,2070,2085,2091,2096,2096,2094,2087,2085,2082,2069,2047,2038,2049,2054,2048,2044,2049,2056,2067,2074,2077,2080,2088,2089,2090,2087,2081,2068,2065,2070,2073,2069,2063,2060,2060,2053,2035,2022,2022,2023,2016,2006,2001,2000,1998,1980,1954,1939,1927,1923,1935,1954,1987,2012,2018,2023,2041,2061,2088,2102,2108,2119,2128,2128,2131,2128,2123,2121,2110,2086,2073,2062,2052,2047,2044,2035,2039,2040,2039,2071,2041,2042,2049,2058,2062,2065,2065,2072,2078,2075,2066,2062,2070,2068,2074,2075,2071,2078,2081,2082,2094,2092,2086,2081,2075,2069,2070,2067,2064,2058,2064,2070,2074,2077,2078,2079,2078,2079,2077,2076,2075,2071,2056,2043,2035,2034,2031,2028,2013,1998,1994,1994,1991,1984,1974,1965,1961,1961,1966,1970,1991,1997,2005,2017,2035,2053,2079,2095,2100,2110,2122,2132,2136,2138,2136,2133,2125,2113,2101,2092,2081,2065,2051,2039,2037,2033,2031,2034,2040,2045,2058,2058,2059,2061,2066,2067,2072,2070,2074,2075,2077,2078,2075,2077,2072,2074,2073,2073,2076,2081,2077,2067,2065,2068,2069,2074,2083,2082,2079,2084,2079,2078,2078,2075,2072,2069,2066,2066,2063,2062,2058,2049,2046,2038,2037,2035,2035,2027,2019,2011,2007,2004,1995,1975,1954,1948,1949,1951,1958,1966,1977,1994,2020,2044,2075,2096,2113,2125,2136,2142,2144,2140,2132,2123,2107,2098,2083,2067,2060,2051,2037,2019,2014,2020,2035,2043,2042,2041,2048,2059,2062,2064,2065,2069,2079,2081,2074,2066,2066,2067,2067,2063,2052,2051,2055,2062,2061,2058,2058,2060,2066,2073,2061,2056,2067,2071,2075,2078,2072,2075,2084,2082,2083,2078,2074,2075,2069,2067,2059,2049,2050,2044,2028,2018,2007,1997,1996,1996,1994,1988,1980,1978,1974,1971,1965,1964,1966,1976,1980,1991,1999,2011,2024,2044,2059,2073,2078,2086,2103,2114,2120,2120,2122,2116,2109,2126,2082,2077,2066,2063,2050,2035,2023,2024,2030,2034,2034,2036,2040,2046,2054,2051,2052,2057,2059,2062,2065,2061,2062,2065,2061,2054,2045,2042,2047,2050,2052,2050,2053,2059,2068,2067,2063,2065,2072,2076,2078,2084,2079,2083,2077,2073,2073,2069,2067,2068,2060,2050,2048,2042,2042,2041,2036,2032,2028,2028,2022,2017,2012,2003,1998,1998,1989,1978,1966,1966,1962,1964,1968,1971,1983,1996,2012,2034,2050,2075,2092,2099,2106,2112,2117,2123,2123,2115,2109,2101,2097,2093,2081,2066,2055,2050,2045,2040,2038,2033,2036,2043,2044,2043,2051,2054,2058,2057,2053,2057,2059,2060,2068,2071,2073,2073,2072,2076,2075,2072,2070,2069,2068,2065,2064,2072,2070,2064,2067,2066,2073,2079,2077,2072,2075,2077,2077,2078,2074,2070,2066,2068,2069,2066,2060,2057,2050,2046,2045,2039,2031,2031,2028,2024,2014,2013,2003,1996,1989,1977,1965,1964,1966,1974,1990,1998,2010,2026,2046,2063,2082,2095,2107,2117,2122,2125,2127,2128,2119,2109,2099,2087,2075,2071,2063,2057,2045,2040,2038,2044,2050,2053,2050,2053,2058,2064,2069,2068,2066,2067,2069,2066,2066,2065,2065,2070,2073,2077,2075,2078,2077,2076,2074,2072,2069,2068,2074,2075,2066,2069,2073,2076,2077,2076,2073,2074,2081,2084,2081,2082,2081,2079,2076,2077,2071,2062,2054,2046,2040,2032,2023,2022,2024,2020,2019,2012,2005,2001,1991,1984,1974,1970,1973,1983,1984,2020,1999,2009,2030,2049,2064,2079,2091,2100,2110,2114,2120,2125,2118,2108,2103,2097,2087,2079,2068,2066,2061,2048,2051,2046,2049,2049,2050,2049,2054,2056,2062,2062,2064,2066,2063,2067,2071,2072,2071,2076,2074,2073,2072,2072,2069,2070,2069,2068,2070,2067,2068,2070,2070,2071,2070,2075,2078,2079,2081,2081,2079,2080,2082,2078,2073,2073,2073,2068,2066,2065,2064,2061,2053,2050,2042,2039,2034,2028,2021,2021,2015,2007,1998,1988,1979,1976,1970,1970,1973,1982,1990,2002,2011,2025,2046,2062,2079,2089,2098,2111,2114,2117,2113,2110,2105,2100,2093,2086,2079,2068,2059,2052,2050,2046,2045,2043,2042,2048,2049,2050,2052,2055,2055,2057,2058,2059,2059,2063,2065,2069,2064,2065,2070,2071,2071,2071,2069,2071,2070,2065,2064,2064,2062,2062,2059,2059,2058,2064,2064,2070,2075,2077,2077,2079,2080,2078,2076,2074,2071,2066,2061,2054,2050,2048,2043,2035,2033,2029,2025,2021,2018,2016,2015,2008,2005,1997,1986,1978,1970,1974,1978,1980,1991,1998,2010,2027,2040,2053,2071,2079,2092,2100,2106,2111,2111,2109,2104,2097,2091,2085,2079,2071,2065,2059,2054,2053,2049,2045,2042,2040,2040,2039,2041,2042,2045,2044,2052,2056,2055,2058,2065,2068,2069,2065,2067,2068,2072,2069,2070,2068,2064,2059,2058,2054,2053,2055,2057,2054,2057,2061,2065,2069,2074,2076,2081,2077,2074,2074,2071,2073,2070,2066,2065,2058,2050,2048,2044,2039,2033,2031,2025,2021,2018,2019,2014,2007,2006,1999,1991,1985,1972,1970,1979,1990,1995,1998,2016,2026,2042,2055,2069,2082,2095,2103,2109,2114,2111,2111,2111,2108,2097,2090,2076,2071,2064,2057,2053,2048,2042,2038,2043,2041,2043,2043,2047,2053,2053,2052,2055,2060,2061,2064,2064,2067,2067,2072,2073,2072,2075,2071,2072,2068,2065,2059,2057,2054,2053,2060,2058,2058,2064,2064,2063,2073,2072,2074,2074,2078,2081,2081,2080,2076,2079,2076,2071,2065,2059,2057,2052,2044,2040,2036,2030,2027,2024,2017,2015,2011,2008,2003,1992,1984,1976,1981,1984,1992,2001,2006,2018,2027,2042,2059,2069,2083,2095,2104,2109,2111,2107,2111,2108,2102,2096,2087,2081,2076,2065,2059,2054,2047,2043,2038,2038,2040,2037,2042,2046,2049,2054,2057,2057,2058,2064,2068,2071,2074,2075,2075,2074,2073,2073,2072,2069,2067,2063,2057,2055,2052,2052,2057,2059,2058,2066,2067,2068,2074,2074,2075,2078,2082,2081,2079,2081,2078,2076,2071,2064,2057,2054,2048,2046,2038,2036,2031,2027,2026,2021,2018,2016,2010,2002,1993,1987,1980,1979,1980,1988,1994,2003,2014,2027,2042,2051,2066,2081,2096,2102,2107,2115,2111,2111,2111,2105,2098,2092,2079,2074,2063,2057,2050,2045,2040,2040,2037,2039,2038,2036,2040,2040,2044,2049,2051,2054,2059,2063,2064,2070,2071,2072,2068,2074,2069,2066,2066,2066,2063,2064,2063,2061,2062,2061,2060,2058,2061,2062,2065,2068,2072,2074,2077,2079,2075,2076,2075,2073,2066,2066,2065,2059,2055,2053,2048,2042,2034,2031,2024,2022,2019,2011,2010,2005,1994,1987,1983,1977,1975,1979,1980,1988,2004,2016,2025,2039,2053,2070,2083,2096,2105,2111,2114,2113,2111,2107,2102,2095,2087,2075,2067,2058,2052,2046,2039,2037,2036,2036,2037,2037,2039,2041,2043,2045,2048,2051,2054,2057,2062,2065,2069,2071,2072,2073,2073,2071,2070,2069,2069,2068,2068,2067,2067,2067,2067,2064,2065,2063,2066,2067,2068,2072,2069,2070,2073,2073,2070,2070,2069,2062,2058,2056,2053,2049,2045,2039,2032,2032,2027,2020,2015,2011,2004,1998,1995,1988,1986,1985,1992,1998,2001,2011,2021,2033,2045,2057,2069,2085,2096,2104,2111,2111,2111,2115,2113,2107,2101,2095,2084,2077,2070,2063,2054,2048,2045,2040,2039,2038,2040,2043,2044,2045,2048,2054,2054,2060,2061,2066,2067,2070,2072,2075,2073,2075,2075,2073,2074,2071,2072,2072,2067,2067,2065,2065,2065,2063,2064,2064,2063,2064,2068,2067,2070,2073,2071,2072,2069,2066,2069,2068,2066,2061,2057,2054,2052,2045,2040,2037,2035,2030,2029,2025,2022,2022,2019,2017,2016,2010,2009,2005,2008,2006,2009,2015,2024,2034,2041,2048,2056,2066,2074,2083,2089,2092,2093,2096,2093,2092,2091,2087,2082,2076,2075,2066,2060,2056,2052,2049,2048,2051,2045,2043,2044,2046,2048,2050,2050,2055,2054,2053,2056,2059,2061,2064,2064,2064,2067,2065,2066,2066,2061,2061,2060,2059,2055,2058,2058,2056,2056,2055,2055,2059,2053,2055,2058,2057,2056,2057,2058,2055,2056,2057,2053,2054,2053,2052,2048,2047,2046,2043,2043,2040,2041,2039,2038,2040,2040,2041,2040,2039,2040,2039,2035,2035,2038,2035,2036,2034,2035,2033,2037,2037,2037,2042,2045,2045,2052,2055,2058,2060,2065,2064,2065,2067,2068,2066,2068,2067,2065,2064,2061,2060,2056,2058,2056,2053,2052,2055,2054,2052,2052,2053,2051,2052,2054,2054,2056,2056,2056,2058,2058,2059,2058,2058,2059,2054,2057,2056,2055,2058,2057,2057,2060,2057,2056,2055,2057,2059,2055,2054,2052,2054,2054,2051,2051,2051,2047,2045,2041,2040,2039,2033,2035,2035,2036,2037,2034,2034,2033,2032,2034,2035,2039,2040,2041,2049,2054,2056,2061,2064,2068,2069,2067,2070,2071,2070,2071,2071,2070,2070,2064,2063,2065,2060,2060,2058,2058,2057,2059,2058,2056,2057,2058,2056,2053,2054,2050,2049,2050,2052,2051,2052,2054,2051,2055,2057,2057,2059,2060,2060,2060,2059,2061,2058,2055,2059,2057,2059,2056,2056,2056,2053,2053,2052,2055,2054,2054,2052,2056,2056,2058,2059,2060,2061,2062,2061,2063,2059,2063,2060,2057,2067,2057,2057,2059,2059,2055,2056,2055,2055,2056,2056,2056,2057,2057,2059,2058,2061,2062,2062,2061,2062,2063,2062,2063,2066,2065,2064,2064,2061,2061,2062,2061,2063,2060,2058,2086,2055,2056,2054,2054,2053,2053,2056,2059,2058,2056,2058,2059,2062,2063,2061,2064,2065,2064,2064,2064,2067,2063,2062,2063,2063,2063,2061,2060,2058,2059,2059,2055,2056,2055,2056,2057,2057,2054,2057,2055,2055,2055,2057,2055,2056,2055,2059,2059,2059,2060,2057,2058,2062,2058,2059,2058,2057,2056,2108,2089,2067,2067,2065,2063,2054,2049,2058,2059,2055,2056,2054,2052,2045,2046,2042,2047,2053,2056,2083,2074,2054,2050,2056,2060,2056,2044,2050,2053,2056,2052,2051,2053,2057,2055,2056,2065,2067,2060,2061,2057,2047,2048,2056,2056,2049,2048,2042,2050,2053,2054,2052,2054,2046,2048,2051,2056,2056,2060,2058,2058,2055,2051,2041,2043,2047,2048,2043,2044,2046,2044,2045,2044,2045,2050,2053,2055,2049,2049,2054,2051,2049,2052,2046,2045,2047,2049,2047,2047,2045,2046,2039,2038,2042,2044,2050,2049,2044,2045,2048,2051,2052,2046,2044,2049,2047,2041,2046,2044,2043,2041,2044,2045,2044,2045,2046,2044,2044,2049,2050,2050,2050,2050,2050,2050,2050,2050,2049,2048,2050,2051,2051,2047,2044,2045,2049,2051,2050,2051,2053,2052,2053,2051,2054,2055,2054,2055,2052,2050,2051,2053,2051,2051,2051,2050,2053,2054,2055,2052,2051,2051,2058,2052,2049,2047,2053,2052,2057,2056,2057,2059,2055,2059,2056,2058,2058,2056,2056,2051,2052,2055,2051,2054,2051,2050,2053,2052,2050,2052,2052,2053,2053,2053,2060,2055,2056,2088,2058,2060,2055,2053,2057,2056,2055,2055,2054,2053,2052,2049,2053,2055,2051,2052,2055,2056,2057,2052,2056,2058,2062,2060,2058,2059,2072,2072,2074,2079,2070,2075,2076,2073,2071,2064,2062,2058,2062,2056,2047,2043,2049,2062,2062,2045,2051,2060,2071,2073,2062,2062,2069,2068,2064,2057,2049,2046,2043,2037,2031,2023,2022,2022,2016,2015,2010,2016,2022,2025,2027,2032,2042,2050,2061,2072,2078,2088,2092,2097,2109,2111,2114,2113,2108,2111,2106,2096,2092,2083,2076,2074,2065,2060,2052,2055,2054,2051,2047,2042,2044,2041,2034,2017,2011,2005,1993,1978,1960,1933,1916,1900,1915,1955,1982,2013,2042,2076,2126,2153,2160,2156,2150,2159,2155,2116,2081,2074,2066,2055,2026,2003,2014,2027,2040,2043,2052,2076,2102,2111,2109,2105,2103,2101,2093,2068,2051,2042,2043,2040,2027,2031,2045,2065,2073,2067,2078,2093,2096,2094,2084,2074,2071,2062,2052,2042,2034,2036,2037,2035,2037,2044,2059,2064,2066,2063,2069,2070,2066,2060,2052,2049,2049,2046,2042,2039,2044,2049,2052,2055,2064,2079,2087,2076,2076,2078,2079,2072,2058,2057,2056,2052,2044,2035,2038,2040,2039,2046,2053,2059,2074,2076,2076,2077,2075,2077,2065,2058,2053,2049,2048,2033,2027,2028,2027,2017,2011,2014,2016,2017,2008,2016,2023,2025,2024,2023,2024,2027,2024,2025,2024,2026,2032,2034,2051,2053,2053,2060,2059,2057,2062,2056,2061,2057,2049,2076,2042,2041,2057,2058,2065,2078,2075,2080,2088,2083,2083,2082,2081,2080,2073,2072,2069,2061,2055,2052,2050,2046,2040,2039,2049,2048,2045,2042,2041,2040,2036,2032,2035,2030,2032,2026,2026,2028,2029,2025,2021,2016,2017,2018,2017,2021,2024,2035,2049,2054,2059,2068,2074,2072,2071,2067,2068,2075,2072,2067,2069,2078,2079,2079,2076,2077,2081,2085,2078,2073,2078,2078,2078,2074,2072,2073,2072,2075,2074,2074,2076,2084,2082,2081,2082,2081,2073,2066,2053,2047,2045,2036,2027,2024,2024,2013,2007,2003,2001,1997,1987,1974,1946,1935,1959,1936,1979,2022,2022,2047,2082,2096,2098,2083,2098,2110,2106,2094,2084,2092,2094,2077,2064,2059,2064,2062,2053,2061,2068,2077,2077,2078,2082,2087,2082,2075,2071,2071,2070,2067,2060,2056,2058,2063,2061,2056,2059,2062,2061,2058,2056,2055,2062,2059,2056,2057,2062,2062,2064,2060,2061,2063,2063,2059,2053,2055,2058,2052,2051,2051,2055,2062,2061,2060,2068,2070,2071,2070,2068,2070,2069,2062,2058,2054,2053,2052,2051,2049,2049,2052,2054,2057,2060,2065,2066,2064,2064,2065,2066,2059,2053,2054,2049,2048,2046,2043,2043,2048,2046,2051,2052,2052,2058,2053,2056,2052,2047,2049,2045,2041,2042,2037,2040,2040,2041,2041,2043,2048,2053,2057,2061,2060,2064,2068,2064,2063,2059,2056,2051,2051,2048,2049,2045,2044,2057,2049,2047,2048,2052,2053,2053,2053,2059,2062,2062,2086,2056,2057,2055,2054,2052,2054,2056,2056,2054,2053,2056,2051,2048,2046,2050,2053,2045,2048,2047,2048,2056,2049,2049,2055,2056,2059,2057,2062,2062,2059,2059,2058,2058,2054,2055,2057,2057,2057,2057,2055,2056,2057,2052,2059,2060,2057,2060,2057,2060,2061,2059,2057,2059,2059,2060,2058,2052,2057,2054,2055,2049,2044,2041,2043,2042,2039,2039,2041,2045,2042,2045,2046,2050,2057,2054,2058,2057,2055,2051,2044,2043,2040,2040,2042,2039,2043,2048,2051,2048,2052,2054,2055,2059,2055,2057,2059,2055,2053,2052,2053,2052,2049,2050,2054,2055,2051,2054,2055,2056,2057,2057,2051,2052,2051,2051,2050,2048,2046,2048,2049,2046,2044,2047,2051,2047,2050,2050,2054,2052,2052,2053,2056,2052,2051,2050,2052,2049,2048,2047,2047,2050,2050,2050,2052,2054,2054,2056,2056,2060,2060,2060,2059,2058,2052,2053,2050,2050,2047,2046,2046,2044,2045,2049,2052,2055,2058,2060,2065,2067,2065,2063,2063,2062,2058,2056,2052,2053,2050,2047,2048,2046,2049,2052,2051,2054,2055,2061,2059,2056,2059,2059,2060,2055,2053,2056,2054,2051,2052,2052,2053,2052,2051,2054,2057,2056,2057,2056,2060,2060,2048,2058,2058,2057,2056,2056,2055,2056,2055,2053,2053,2057,2055,2053,2056,2055,2052,2053,2055,2053,2055,2056,2057,2055,2056,2059,2060,2058,2058,2054,2058,2057,2055,2056,2057,2058,2055,2055,2056,2061,2057,2063,2060,2065,2066,2064,2091,2060,2060,2058,2060,2058,2059,2061,2061,2059,2055,2058,2062,2059,2057,2058,2058,2061,2060,2058,2058,2058,2054,2052,2053,2056,2057,2055,2055,2053,2058,2059,2057,2055,2060,2059,2055,2056,2058,2054,2055,2051,2053,2054,2054,2052,2055,2055,2057,2057,2058,2056,2059,2058,2059,2060,2057,2058,2057,2055,2054,2053,2055,2056,2058,2056,2056,2058,2061,2060,2057,2056,2056,2053,2056,2056,2053,2059,2058,2056,2056,2059,2056,2057,2058,2056,2060,2059,2058,2059,2056,2056,2057,2056,2052,2052,2053,2052,2050,2049,2051,2049,2051,2053,2051,2052,2054,2054,2055,2056,2057,2054,2055,2055,2055,2058,2057,2054,2051,2049,2051,2050,2050,2049,2049,2052,2053,2053,2054,2052,2054,2052,2052,2052,2052,2054,2053,2052,2051,2057,2054,2055,2053,2055,2058,2054,2054,2053,2056,2055,2051,2051,2050,2052,2051,2049,2049,2052,2054,2052,2051,2053,2055,2054,2053,2054,2056,2055,2055,2053,2050,2054,2052,2055,2053,2051,2049,2052,2056,2054,2053,2054,2054,2054,2052,2054,2056,2056,2054,2054,2053,2053,2054,2050,2050,2054,2053,2056,2057,2057,2056,2058,2055,2055,2056,2056,2054,2055,2054,2055,2054,2055,2057,2053,2056,2055,2055,2056,2056,2053,2058,2060,2053,2055,2054,2053,2052,2057,2047,2052,2057,2056,2055,2055,2057,2056,2054,2056,2055,2056,2057,2056,2055,2056,2059,2062,2061,2060,2056,2058,2059,2058,2054,2060,2056,2054,2084,2056,2054,2053,2056,2055,2053,2058,2056,2054,2054,2053,2054,2054,2055,2056,2054,2055,2056,2057,2058,2060,2057,2057,2060,2060,2058,2060,2056,2057,2055,2053,2052,2052,2052,2052,2056,2057,2056,2054,2055,2055,2056,2058,2060,2058,2058,2060,2060,2058,2058,2059,2062,2062,2057,2056,2057,2058,2055,2056,2057,2054,2056,2059,2056,2055,2057,2058,2058,2059,2059,2060,2058,2058,2059,2058,2061,2060,2058,2058,2058,2058,2057,2059,2057,2057,2059,2058,2057,2053,2059,2063,2066,2056,2048,2046,2058,2065,2066,2052,2050,2052,2062,2064,2060,2056,2055,2059,2062,2059,2062,2059,2057,2051,2051,2056,2057,2059,2055,2054,2053,2060,2061,2056,2055,2056,2061,2058,2057,2057,2055,2055,2056,2055,2055,2055,2058,2054,2055,2053,2056,2060,2057,2058,2058,2058,2057,2054,2057,2056,2054,2055,2054,2049,2054,2054,2055,2056,2055,2056,2058,2055,2056,2053,2055,2053,2051,2053,2053,2052,2052,2054,2053,2051,2053,2052,2053,2051,2052,2052,2051,2053,2050,2050,2053,2053,2054,2053,2054,2053,2054,2052,2052,2053,2054,2054,2051,2052,2052,2052,2051,2054,2053,2053,2054,2050,2052,2051,2052,2052,2054,2052,2052,2053,2052,2053,2053,2051,2051,2050,2052,2054,2050,2051,2049,2049,2047,2048,2050,2048,2047,2048,2050,2050,2051,2049,2047,2046,2045,2045,2045,2044,2047,2045,2044,2047,2048,2048,2047,2044,2045,2045,2047,2049,2047,2044,2074,2047,2045,2044,2042,2044,2044,2045,2046,2043,2042,2044,2045,2048,2049,2047,2049,2049,2050,2052,2048,2054,2052,2053,2049,2048,2051,2051,2049,2049,2051,2049,2049,2050,2052,2053,2052,2051,2053,2055,2055,2051,2051,2050,2052,2054,2052,2055,2055,2053,2054,2054,2055,2055,2056,2056,2054,2056,2057,2059,2058,2055,2057,2056,2056,2055,2057,2053,2055,2054,2052,2056,2056,2055,2055,2055,2055,2055,2057,2055,2055,2058,2059,2055,2056,2058,2058,2057,2055,2053,2053,2055,2056,2055,2056,2053,2054,2057,2057,2055,2056,2055,2059,2055,2057,2057,2057,2054,2054,2053,2056,2057,2054,2055,2054,2055,2055,2054,2055,2057,2056,2058,2057,2055,2054,2057,2054,2055,2053,2054,2054,2056,2058,2057,2059,2059,2058,2056,2055,2055,2058,2057,2057,2059,2057,2056,2057,2059,2058,2054,2056,2056,2055,2056,2058,2057,2059,2059,2058,2059,2059,2061,2057,2058,2059,2059,2060,2057,2057,2055,2057,2058,2056,2057,2057,2056,2060,2061,2060,2060,2060,2058,2057,2058,2059,2059,2064,2060,2058,2058,2059,2060,2056,2061,2059,2062,2060,2060,2060,2062,2062,2059,2059,2062,2058,2059,2061,2060,2061,2059,2059,2057,2059,2061,2059,2061,2063,2059,2061,2061,2059,2062,2060,2059,2056,2056,2056,2057,2056,2055,2056,2052,2054,2057,2053,2055,2053,2053,2058,2057,2054,2055,2056,2056,2055,2060,2056,2055,2057,2055,2054,2053,2054,2057,2054,2055,2086,2055,2055,2056,2056,2055,2053,2055,2052,2058,2054,2054,2055,2055,2053,2054,2054,2055,2056,2058,2054,2058,2057,2057,2053,2053,2055,2053,2054,2055,2053,2056,2055,2056,2059,2055,2053,2055,2055,2058,2054,2054,2057,2055,2055,2054,2052,2056,2055,2054,2054,2053,2054,2052,2053,2052,2052,2052,2050,2051,2050,2051,2052,2053,2049,2052,2051,2050,2050,2051,2050,2053,2053,2051,2052,2054,2050,2052,2051,2050,2051,2052,2050,2049,2051,2052,2049,2050,2051,2051,2051,2049,2050,2048,2053,2052,2051,2051,2051,2047,2048,2052,2052,2051,2052,2051,2050,2051,2048,2051,2049,2050,2051,2053,2050,2051,2051,2051,2052,2051,2052,2052,2051,2052,2049,2051,2053,2052,2052,2051,2050,2050,2049,2049,2052,2052,2050,2051,2052,2053,2052,2051,2049,2050,2051,2050,2052,2052,2053,2053,2053,2053,2053,2055,2054,2055,2054,2053,2056,2055,2055,2056,2054,2052,2056,2054,2059,2055,2055,2056,2055,2058,2058,2057,2058,2054,2056,2059,2058,2057,2058,2058,2060,2058,2056,2061,2060,2058,2059,2060,2060,2059,2060,2059,2059,2060,2062,2062,2061,2060,2061,2059,2061,2059,2058,2059,2060,2060,2060,2060,2057,2058,2059,2058,2058,2060,2060,2061,2059,2057,2057,2059,2056,2057,2056,2057,2054,2057};

// Define hmm struct

//Define struct
typedef struct speech speech;
struct speech{
	arm_matrix_instance_f32* mu;
	arm_matrix_instance_f32* sig;
	arm_matrix_instance_f32* inv;
	float32_t* det;

};

/*Defines*/
#define NUMBER_OF_WORDS 2
#define MAX_SEQ_PER_WORD 20
#define MAX_SEQUENCES_PER_SEQ 20
#define MATH_PI 3.141592653589793
#define NUMBER_OF_STATES 8
#define A_SIZE NUMBER_OF_STATES*NUMBER_OF_STATES
#define NUMBER_OF_MFCC 13
#define PATH_LENGTH 5
#define TRANS_PATH_LENGTH 10
#define FRAME_LENGTH 256
#define VEC_LENGTH 9000

/*MFCC*/
void simple_mel_extractor_v2(arm_matrix_instance_f32 *frame_power, arm_matrix_instance_f32 *MFCC_mat);

/*Lexicon*/
void initLexicon() ;
void sequenceConverter(uint8_t* outSequence, uint8_t* inSequence, uint8_t length);
void searchPattern(uint8_t* output, uint8_t* sequence,uint8_t length);
void framer(float32_t *in_vec,int length_in_vec,float32_t *frame,int frame_length,int frame_nr);
void windower(float32_t *window,float32_t *frame,int frame_length);
void preprocessing(float32_t *frame,float32_t *fft_frame,float32_t *window,int frame_size);
void logp_xn_zn(arm_matrix_instance_f32 observ,speech *mu_sig,arm_matrix_instance_f32 *xn_zn,uint8_t n_states,uint8_t n_features);
void MatrixMax(arm_matrix_instance_f32 *C,uint8_t col,float32_t *max,uint16_t *ind);
void MatVecMax(arm_matrix_instance_f32 *C,float32_t *max,uint16_t *ind);
void viterbi_log_NR(arm_matrix_instance_f32 *A,arm_matrix_instance_f32 *xn_zn,arm_matrix_instance_f32 *path,arm_matrix_instance_f32 *logV,uint8_t path_length,uint8_t n_states);
void path_filter(arm_matrix_instance_f32 *path,arm_matrix_instance_f32 *filtered_path,uint8_t path_length);
void trans_path(arm_matrix_instance_f32 *filtered_path,uint8_t *trans_path,uint8_t filtered_path_length,uint8_t trans_path_length);
void run_all();
void preEmphasis(float32_t *in_vec,int length_in_vec,float32_t *out_vec);
float32_t returnMax(float32_t *in,float32_t inLength);

#endif
