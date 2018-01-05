GOLDENDIR=./golden-images
OUTPUTDIR=./output

.PHONY : all golden clean veryclean

all:
	@rm -rf $(OUTPUTDIR)
	@./test.sh 2> /dev/null

golden: | $(GOLDENDIR)
	@./make-golden.sh

$(GOLDENDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OUTPUTDIR)

veryclean: clean
	@rm -rf $(GOLDENDIR)
