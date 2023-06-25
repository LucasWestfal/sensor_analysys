library(rstan)
# The model is written in a string. I can also be in a file.
# Note that comments in the Stan language follow '//'
stanmodelcode <- "
data {            // data block for data declarations
  int<lower=0> N;
  int y[N];
}
parameters {      // parameter block for parameter declarations
  real<lower=0,upper=1> theta;
}
model {  // model block: priors for parameters and model for data
  theta ~ beta(1,1);  // not really needed since it's uniform (the default)
  y ~ bernoulli(theta); // y is a vector but this works
}
"
# Create the data if it doesn't already exist
N <- 20
y <- rbinom(N, 1, .3)
# put it in a list
dat <- list(N = N, y = y) # note that 'dat' is a list, not necessarily a data.frame
sapply(dat, class)
# Stan may take a long time in the compiling step below:
system.time(
  fit <- stan(model_code = stanmodelcode, 
              model_name = "Bernoulli Beta(1,1)",
              data = dat, 
              iter = 2012, 
              chains = 4, 
              sample_file = 'norm.csv',
              verbose = TRUE)
)
# We can print and plot the fit
class(fit)
methods(class = 'stanfit')
print(fit)
traceplot(fit)
traceplot(fit, 'theta', inc_warmup = TRUE)
plot(fit)

# extract samples

e <- extract(fit) # return a list of arrays
str(e)
acf(e$theta)
densityplot(e$theta, xlim = c(0,1))