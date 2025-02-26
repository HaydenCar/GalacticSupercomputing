/*
 * $HEADER$
 */
#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

extern const pmix_mca_base_component_t pmix_mca_pnet_opa_component;

const pmix_mca_base_component_t *pmix_mca_pnet_base_static_components[] = {
  &pmix_mca_pnet_opa_component, 
  NULL
};

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif

