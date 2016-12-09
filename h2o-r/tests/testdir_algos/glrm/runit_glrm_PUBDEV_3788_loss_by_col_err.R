setwd(normalizePath(dirname(R.utils::commandArgs(asValues=TRUE)$"f")))
source("../../../scripts/h2o-r-test-setup.R")

# error accessing archetypes: Error in res$model_metrics[[1L]] : subscript out of bounds
# make sure we pass this one after the fix.
test.glrm.pubdev.3788 <- function() {
    # Create data frame with a constant column
    data <- data.frame('NumericCol' = runif(50),
    'ConstantCol' = rep(1, 50),
    'CategoricalCol' = sample(c("A", "B", "C", "D"), size = 50, replace = T))

    data <- as.h2o(data)

    # Specify loss by column and set ignore_const_cols to TRUE
    glrm_model <- h2o.glrm(data, k = 2, model_id = "glrm_test.hex",
    loss_by_col = c("Quadratic", "Quadratic", "Categorical"),
    loss_by_col_idx = c(0:2),
    ignore_const_cols = TRUE)

    archetypes <- h2o.proj_archetypes(glrm_model, data)  # make sure returned archetypes are not empty
  
}

doTest("GLRM Test: Iris with Various Transformations", test.glrm.pubdev.3788)
