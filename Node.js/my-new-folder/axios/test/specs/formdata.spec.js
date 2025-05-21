import {retryNetwork} from "../helpers/retry.js";

describe('FormData', function() {
  it('should allow FormData posting', async () => {
    await retryNetwork(() => {
      return axios.postForm('http://httpbin.org/post', {
        a: 'foo',
        b: 'bar'
      }).then(({data}) => {
        expect(data.form).toEqual({
          a: 'foo',
          b: 'bar'
        });
      });
    });
  });
})
