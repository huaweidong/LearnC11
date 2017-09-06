#include <random>
#include <iostream>
#include <functional>

int main()
{
    std::default_random_engine generator(time(NULL));  // 生成器
    std::uniform_int_distribution<int> dis(0,100);      // 分布器
    auto dice= std::bind(dis,generator);
    for(int i=0;i<5;i++)  
    {  
        //std::cout<<dis(generator)<<std::endl;  
        std::cout<<dice()<<std::endl;  
    }  
}

/*
uniform_int_distribution           整数均匀分布
uniform_real_distribution         浮点数均匀分布
bernoulli_distribution     伯努利分布
binomial_distribution      二项分布
geometry_distribution     几何分布
negative_biomial_distribution   负二项分布
poisson_distribution  泊松分布
exponential_distribution 指数分布
gamma_distribution 伽马分布
weibull_distribution 威布尔分布
extreme_value_distribution 极值分布
normal_distribution         正态分布
chi_squared_distribution 卡方分布
cauchy_distribution        柯西分布
fisher_f_distribution       费歇尔F分布
student_t_distribution  t分布
discrete_distribution 离散分布
piecewise_constant_distribution 分段常数分布
piecewise_linear_distribution 分段线性分布
*/
