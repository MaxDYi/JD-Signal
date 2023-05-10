cmake_minimum_required (VERSION 3.14)



target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_boolean_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_braycurtis_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_canberra_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_chebyshev_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_chebyshev_distance_f64.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_cityblock_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_cityblock_distance_f64.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_correlation_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_cosine_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_cosine_distance_f64.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_dice_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_euclidean_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_euclidean_distance_f64.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_hamming_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_jaccard_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_jensenshannon_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_kulsinski_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_minkowski_distance_f32.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_rogerstanimoto_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_russellrao_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_sokalmichener_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_sokalsneath_distance.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_yule_distance.c)


target_include_directories(CMSISDSP PRIVATE "DistanceFunctions")

if ((NOT ARMAC5) AND (NOT DISABLEFLOAT16))
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_braycurtis_distance_f16.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_canberra_distance_f16.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_chebyshev_distance_f16.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_cityblock_distance_f16.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_correlation_distance_f16.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_cosine_distance_f16.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_euclidean_distance_f16.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_jensenshannon_distance_f16.c)
target_sources(CMSISDSP PRIVATE DistanceFunctions/arm_minkowski_distance_f16.c)
endif()

 