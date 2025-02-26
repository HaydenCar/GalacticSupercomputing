/*
 * $HEADER$
 */
#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

extern const pmix_mca_base_component_t prte_mca_prtereachable_weighted_component;
extern const pmix_mca_base_component_t prte_mca_prtereachable_netlink_component;

const pmix_mca_base_component_t *prte_prtereachable_base_static_components[] = {
  &prte_mca_prtereachable_weighted_component, 
  &prte_mca_prtereachable_netlink_component, 
  NULL
};

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif

